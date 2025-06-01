#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <utmp.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#include "linkedlist.h"

int checkUsername(const char* username);

Node* readWTMP(const char* file);

int main(int argc, char * argv[])
{
    char filename[2048];
    strcpy(filename,"/var/log/wtmp");

    const char *users[100] = { NULL };
    int userCount = 0;
    char *date = NULL;
    char *time = NULL;

    int opt = 0;

    while ((opt = getopt(argc, argv, "u:d:t:f:")) != -1)
    {
            switch (opt)
            {
                case 'u':
                {
                    // Parse user list (comma separated)
                    char *userList = optarg;
                    char *user = strtok(userList, ",");
                    while (user)
                    {
                        if (!checkUsername(user))
                        {
                            return 1;
                        }
                        users[userCount++] = user;
                        user = strtok(NULL, ",");
                    }
                    break;
                }
                case 'd':
                    // Set the date filter
                    date = optarg;
                    break;
                case 't':
                    // Set the time filter
                    time = optarg;
                    break;
                case 'f':
                    // Set the filename for the log file
                    realpath(optarg, filename);
                    break;
                default:
                    fprintf(stderr, "Usage: %s [-u users] [-d date] [-t time] [-f filename]\n", argv[0]);
                    exit(1);
        }
    }

    // Check for extra non-option arguments
    if (optind < argc)
    {
        fprintf(stderr, "Too many arguments. Extra arguments detected: ");
        for (int i = optind; i < argc; i++)
        {
            fprintf(stderr, "%s ", argv[i]);
        }
        fprintf(stderr, "\n");
        return 1;
    }

    Node* head = readWTMP(filename);
    if (head == NULL)
        return 1;

    if (date != NULL)
    {
        Node* temp = head;

        int month = 0, day = 0, year = 0;

        char *parser = strtok(date, "/");
        if (parser)
            month = atoi(parser);
        parser = strtok(NULL, "/");
        if (parser)
            day = atoi(parser);
        parser = strtok(NULL, "/");
        if (parser)
            year = atoi(parser);

        if (month > 12 || month < 0 || day > 31 || day < 0 || year > 99 || year < 0)
        {
            fprintf(stderr,"Invalid Date\n");
            freeList(head);
            exit(1);
        }

        while (temp != NULL)
        {
            char bufin[80];
            char bufout[80];
            struct tm loginTimeStruct, logoutTimeStruct;
            localtime_r(&temp->record.loginTime, &loginTimeStruct);
            localtime_r(&temp->record.logoutTime, &logoutTimeStruct);
            strftime(bufin, 80, "%m/%d/%y", &loginTimeStruct);
            strftime(bufout, 80, "%m/%d/%y", &logoutTimeStruct);

            int monthIn = 0, dayIn = 0, yearIn = 0;

            parser = strtok(bufin, "/");
            if (parser)
                monthIn = atoi(parser);
            parser = strtok(NULL, "/");
            if (parser)
                dayIn = atoi(parser);
            parser = strtok(NULL, "/");
            if (parser)
                yearIn = atoi(parser);

            int monthOut = 0, dayOut = 0, yearOut = 0;

            parser = strtok(bufout, "/");
            if (parser)
                monthOut = atoi(parser);
            parser = strtok(NULL, "/");
            if (parser)
                dayOut = atoi(parser);
            parser = strtok(NULL, "/");
            if (parser)
                yearOut = atoi(parser);

            //if true, then the user was on during the specified date
            if (((monthOut >= month || temp->record.isLoggedOff == 0) && month >= monthIn) &&
                ((dayOut >= day || temp->record.isLoggedOff == 0) && day >= dayIn) &&
                ((yearOut >= year || temp->record.isLoggedOff == 0) && year >= yearIn)) {

                temp = temp->next;
            }
            else
                temp = deleteNode(&head, temp);

        }
    }
    if (time != NULL)
    {
        Node* temp = head;

        int hour = 0, minute = 0;

        char *parser = strtok(time, ":");
        if (parser)
            hour = atoi(parser);
        parser = strtok(NULL, ":");
        if (parser)
            minute = atoi(parser);

        if (hour > 23 || hour < 0 || minute > 59 || minute < 0)
        {
            fprintf(stderr,"Invalid Time\n");
            freeList(head);
            exit(1);
        }

        while (temp != NULL)
        {
            char bufin[80];
            char bufout[80];
            struct tm loginTimeStruct, logoutTimeStruct;
            localtime_r(&temp->record.loginTime, &loginTimeStruct);
            localtime_r(&temp->record.logoutTime, &logoutTimeStruct);
            strftime(bufin, 80, "%H:%M", &loginTimeStruct);
            strftime(bufout, 80, "%H:%M", &logoutTimeStruct);

            int hourIn = 0, minuteIn = 0;

            parser = strtok(bufin, ":");
            if (parser)
                hourIn = atoi(parser);
            parser = strtok(NULL, ":");
            if (parser)
                minuteIn = atoi(parser);

            int hourOut = 0, minuteOut = 0;

            parser = strtok(bufout, ":");
            if (parser)
                hourOut = atoi(parser);
            parser = strtok(NULL, ":");
            if (parser)
                minuteOut = atoi(parser);

            //if true, then the user was on during the specified date
            if (((hourOut >= hour || temp->record.isLoggedOff == 0) && hour >= hourIn) &&
                ((minuteOut >= minute || temp->record.isLoggedOff == 0) && minute >= minuteIn)) {

                temp = temp->next;
            }
            else
                temp = deleteNode(&head, temp);

        }
    }
    if (userCount > 0)
    {
        Node* temp = head;

        while (temp != NULL)
        {
            int found = 0;

            for (int i = 0; i < userCount; i++)
            {
                if (strcmp(users[i], temp->record.login) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (found == 0)
                temp = deleteNode(&head, temp);
            else
                temp = temp->next;
        }
    }

    /*printf("random\n");
    //randomizeList(&head);
    //printList(head);
    //printf("sort\n");*/

    bubbleSort(&head);
    printList(head);
    freeList(head);

    return 0;
}


int checkUsername(const char* username)
{
    struct passwd *user_info = getpwnam(username);
    if (user_info == NULL)
    {
        fprintf(stderr, "Username '%s' not found\n", username);
        return 0;
    }
    return 1; // Username found
}

Node* readWTMP(const char* filename)
{
    FILE *wtmpFile;
    struct utmp entry;

    Node* head = createNode();
    if (head == NULL)
    {
        exit(1);
    }
    Node* tail = NULL;

    wtmpFile = fopen(filename, "rb");
    if (wtmpFile == NULL)
    {
        fprintf(stderr,"Failed to open %s file\n",filename);
        exit(1);
    }

    struct stat st;
    if (stat(filename, &st) != 0)
    {
        perror("stat");
        exit(1);
    }
    if (st.st_size % sizeof(struct utmp) != 0)
    {
        fprintf(stderr, "%s is not a valid wtmp file (size mismatch)\n", filename);
        fclose(wtmpFile);
        exit(1);
    }


    while (fread(&entry, sizeof(struct utmp), 1, wtmpFile) == 1)
    {
        if (entry.ut_type == USER_PROCESS)
        {
            if (!checkUsername(entry.ut_user) || entry.ut_user[0] == '\0')
            {
                freeList(head);
                exit(1);
            }

            Node* temp = (tail == NULL) ? head : createNode();

            strncpy(temp->record.login, entry.ut_user, UT_NAMESIZE);
            //temp->record.login[UT_NAMESIZE - 1] = '\0';
            strncpy(temp->record.tty, entry.ut_line, UT_LINESIZE);
            //temp->record.tty[UT_LINESIZE- 1] = '\0';
            strncpy(temp->record.from_host, entry.ut_host, UT_HOSTSIZE);
            //temp->record.from_host[UT_HOSTSIZE - 1] = '\0';

            temp->record.loginTime = entry.ut_time;
            temp->record.isLoggedOff = 0;

            Node* temporary = tail;
            while (temporary != NULL)
            {
                if (strcmp(temporary->record.tty, entry.ut_line) == 0 && temporary->record.isLoggedOff == 0)
                {
                    temporary->record.logoutTime = entry.ut_time;
                    temporary->record.isLoggedOff = 1;
                    break;
                }
                temporary = temporary->prev;
            }

            if (tail == NULL)
                pushBack(&head, temp);
            else
                pushBack(&tail, temp);
            tail = temp;

        }
        else if (entry.ut_type == DEAD_PROCESS )
        {
            char buf[UT_LINESIZE];

            strncpy(buf, entry.ut_line, UT_LINESIZE - 1);
            //buf[UT_LINESIZE - 1] = '\0';

            Node* temp = tail;
            while (temp != NULL)
            {
                if (strcmp(temp->record.tty, entry.ut_line) == 0)
                {
                    temp->record.logoutTime = entry.ut_time;
                    temp->record.isLoggedOff = 1;
                    break;
                }
                temp = temp->prev;
            }

            //alternate method to start at beginning of list
            /*Node* temp = head;
            Node* last = NULL;
            while (temp != NULL)
            {
                if (strcmp(temp->record.tty, entry.ut_line) == 0)
                {
                    last = temp;
                }
                temp = temp->next;
            }
            if (last != NULL)
            {
                last->record.logoutTime = entry.ut_time;
                last->record.isLoggedOff = 1;
            }*/
        }
        else if (entry.ut_type == BOOT_TIME)
        {
            Node* temp = head;
            while(temp->next != NULL)
            {
                if (temp->record.isLoggedOff == 0)
                {
                    temp->record.logoutTime = entry.ut_time;
                    temp->record.isLoggedOff = 1;
                }
                temp = temp->next;
            }
        }
    }
    fclose(wtmpFile);

    return head;
}
