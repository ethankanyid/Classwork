#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 4096
#define MAX_URL 2048

/*  helper function to print usage */
void print_usage(void);

/*  takes input line, compiled regex, and parallel status.
    if parallel, forks the function on the next url*/
Node * extract_urls(const char *input, regex_t *regex, int parallel);

/*  checks to see if a link is valid */
int is_url_valid(const char *url);

/*  downloads the content of a url */
Node* download_url_content(const char *url,regex_t *regex, int parallel);

// Regular expression to match href URLs
const char *regex_pattern = "<[^>]*href=(\")?(https?:[^\"#?]*)[^\"]*(\")?[^>]*>";


int main(int argc, char *argv[])
{
    int opt;
    int parallel = 0;
    FILE *input_file = NULL;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "fph")) != -1)
    {
        switch (opt)
        {
            case 'f':
                if (optind < argc)
                {
                    input_file = fopen(argv[optind], "r");
                    if (!input_file)
                    {
                        perror("fopen");
                        exit(EXIT_FAILURE);
                    }
                    optind++;
                }
                else
                {
                    fprintf(stderr, "Option -f requires a filename argument.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p':
                parallel = 1;
                break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    regex_t regex;
    // Compile regex
    if (regcomp(&regex, regex_pattern, REG_EXTENDED | REG_ICASE)) //extended and insensitive
    {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    Node* head = NULL;

    // Process input
    if (input_file)
    {
        char line[MAX_LINE];
        int index = 0;
        int insideTag = 0;

        char ch = 0;
        while ((ch = fgetc(input_file)) != EOF)
        {
            line[index] = ch;

            if (ch == '<')
                insideTag = 1;
            else if (ch == '>')
                insideTag = 0;

            if (ch == '\n' && !insideTag)
            {
                line[index + 1] = '\0';
                Node* temp = extract_urls(line, &regex, parallel);
                if (temp)
                {
                    if (!head)
                        head = temp;
                    pushBack(&head, temp);
                }
                index = 0;
                continue;
            }
            index++;

        }
        fclose(input_file);
    }
    else
    {
        head = download_url_content(argv[optind], &regex, parallel);
    }

    // Wait for any remaining children (if in parallel mode)
    if (parallel)
    {
        while (wait(NULL) > 0);
    }

    bubbleSort(&head);
    checkDups(&head);
    printList(head);
    freeList(head);

    regfree(&regex);
    return 0;
}

void print_usage(void)
{
    printf(
        "Usage: checklinks [options] urlOrFilename\n"
        "\n"
        "Options:\n"
        "  -f            Treat input as a local file instead of a URL\n"
        "  -p            Run in parallel (fork and exec wget for each URL)\n"
        "  -h            Show this help message and exit\n");
}

Node* extract_urls(const char *input, regex_t *regex, int parallel)
{
    regmatch_t matches[4];
    const char *current_pos = input;

    Node* head = NULL;

    while (regexec(regex, current_pos, 4, matches, 0) == 0)
    {
        int urlLen = matches[2].rm_eo - matches[2].rm_so;
        char url[MAX_URL];
        snprintf(url, urlLen + 1, "%.*s", urlLen, current_pos + matches[2].rm_so);

        if (url[urlLen - 1] == '/')
            url[urlLen - 1] = '\0';

        if ((matches[1].rm_so != -1 && matches[3].rm_so == -1) ||
            (matches[3].rm_so != -1 && matches[1].rm_so == -1))
        {
            break;
        }

        Node* newNode = createNode();
        strncpy(newNode->data.url, url, MAX_URL);

        if (parallel)
        {
            int pipefd[2];
            if (pipe(pipefd) == -1)
            {
                perror("pipe failed");
                free(newNode);
                return NULL;
            }

            pid_t pid = fork();

            if (pid == 0)
            {
                // In the child process
                close(pipefd[0]);  // Close unused read end of the pipe

                // Simulate URL validation
                newNode->data.status = is_url_valid(url);

                // Write status to the pipe
                write(pipefd[1], &newNode->data.status, sizeof(int));

                close(pipefd[1]);  // Close write end of the pipe
                exit(0);
            }
            else if (pid < 0)
            {
                perror("fork failed");
                free(newNode);
                return NULL;
            }

            // Parent process reads from the pipe
            close(pipefd[1]);  // Close unused write end of the pipe
            read(pipefd[0], &newNode->data.status, sizeof(int));  // Read status
            close(pipefd[0]);  // Close read end of the pipe
        }
        else
        {
            newNode->data.status = is_url_valid(url);
        }

        if (!head)
            head = newNode;
        else
            pushBack(&head, newNode);

        current_pos += matches[0].rm_eo;
    }

    return head;
}

int is_url_valid(const char *url)
{
    char command[MAX_LINE];
    snprintf(command, sizeof(command), "wget --spider -q '%s'", url);

    int ret = system(command);

    if (ret == -1) {
        perror("system");
        return 0;
    }

    // Extract exit status
    if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

Node* download_url_content(const char *url,regex_t *regex, int parallel)
{
    char command[MAX_LINE];
    snprintf(command, sizeof(command), "wget --no-cache --delete-after -q -O - '%s'", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        return NULL;
    }

    char line[MAX_LINE];
    int index = 0;
    int insideTag = 0;

    Node* head = NULL;

    char ch = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        line[index] = ch;

        if (ch == '<')
            insideTag = 1;
        else if (ch == '>')
            insideTag = 0;

        if (ch == '\n' && !insideTag)
        {
            line[index + 1] = '\0';
            Node* temp = extract_urls(line, regex, parallel);
            if (temp)
            {
                if (!head)
                    head = temp;
                pushBack(&head, temp);
            }
            index = 0;
            continue;
        }
        index++;
    }

    pclose(fp);

    return head;
}
