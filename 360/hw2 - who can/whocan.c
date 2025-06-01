#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

#include "linkedlist.h"

// i hated every second of this assignment. probably some of the worst work ive ever done.
// it is not clear who can execute a file. from what i have read, root can always execute a file.
// it is not clear what is proper error messaging:
//      the sample binary does not output for cd'ing into a file, i do - i consider that an error.
//      same for executing a dir, and searching a file

/*  checks permissions for a single fsobj on read for all*/
static Node* readPermissions(char* path);
/*  checks permissions for a single fsobj on write for all*/
static Node* writePermissions(char* path);
/*  checks permissions for a single fsobj on execute for all*/
static Node* exPermissions(char* path);

/*  returns a valid list of who can execute to a given point.
    is meant to take path of one before item to check because
    it will return up to the last item in the path */
static Node* permToRoot(const char* path);

/*  establishes whether everyone can */
int everyone = 1;

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Invalid command line argument count: expected 2\n");
        return 1;
    }

    char* action = argv[1];
    char* fsobj = argv[2];
    char realPath[1024];

    if (realpath(fsobj, realPath) == NULL)
    {
        fprintf(stderr, "Could not resolve path for %s\n", fsobj);
        return 1;
    }

    //path up until last item
    char* lastSlash = strrchr(realPath, '/');
    size_t len = lastSlash - realPath;
    if (len == 0)
        len = 1;
    char result[len + 1];  // +1 for the null terminator
    strncpy(result, realPath, len);
    result[len] = '\0';
    if (lastSlash == realPath)
        result[0] = '/';

    //permissions to root
    Node* possible = permToRoot(result);

    if (!strcmp(action, "read"))
    {
        Node* read = readPermissions(realPath);
        //check read
        //possible is on the insde because it is the limiter
        if (possible != NULL)
        {
            Node* temp1 = read;
            while (temp1 != NULL)
            {
                Node* temp2 = possible;
                int found = 0;
                while (temp2 != NULL)
                {
                    if (!strcmp(temp1->name,temp2->name))
                    {
                        found = 1;
                        break;
                    }
                    temp2 = temp2->next;
                }
                if (!found)
                {
                    //points to next node by return value
                    temp1 = deleteNode(&read, temp1);
                    everyone = 0;
                }
                else
                    temp1 = temp1->next;
            }
        }

        //push root on
        Node* temp = read;
        int found = 0;
        while (temp != NULL)
        {
            if (!strcmp(temp->name,"root"))
            {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found)
        {
            push_back(&read, "root");
        }

        //print list
        if (everyone)
        {
            printf("everyone\n");
        }
        else
        {
            bubbleSort(&read);
            printList(read);
        }
        freeList(read);
    }
    else if (!strcmp(action, "cd") || !strcmp(action, "search"))
    {
        struct stat tempStat;

        if (stat(realPath, &tempStat) == -1)
        {
            fprintf(stderr,"Stat could not access fsobj\n");
        }

        if(!(S_ISDIR(tempStat.st_mode)))
        {
            fprintf(stderr,"fsobj is not a directory\n");
        }
        else
        {
            //check execute
            Node* execute = exPermissions(realPath);
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = execute;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&execute, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on if not already
            Node* temp = execute;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&execute, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&execute);
                printList(execute);
            }
            freeList(execute);
        }
    }
    else if (!strcmp(action, "execute"))
    {
        struct stat tempStat;

        if (stat(realPath, &tempStat) == -1)
        {
            fprintf(stderr,"Stat could not access fsobj\n");
        }

        if(!(S_ISREG(tempStat.st_mode)))
        {
            fprintf(stderr,"fsobj is not a file\n");
        }
        else
        {
            //check execute
            Node* execute = exPermissions(realPath);
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = execute;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&execute, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on if not already
            Node* temp = execute;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&execute, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&execute);

                //doesnt make sense, but it says execute bit must be set for at least someone in UGO
                //if (execute != NULL && execute->next != NULL && !strcmp("root", execute->name))
                    printList(execute);
            }
            freeList(execute);
        }
    }
    else if (!strcmp(action, "ls"))
    {
        struct stat tempStat;

        if (stat(realPath, &tempStat) == -1)
        {
            fprintf(stderr,"Stat could not access fsobj\n");
        }

        if(S_ISDIR(tempStat.st_mode))
        {
            Node* read = readPermissions(realPath);
            //check read
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = read;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&read, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on
            Node* temp = read;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&read, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&read);
                printList(read);
            }
            freeList(read);
        }
        else // file or device
        {
            //possible returns the list of all execute permissions to the previous directory
            Node* read = possible;

            //push root on
            Node* temp = read;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&read, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&read);
                printList(read);
            }
        }
    }
    else if (!strcmp(action, "write"))
    {
        struct stat tempStat;

        if (stat(realPath, &tempStat) == -1)
        {
            fprintf(stderr,"Stat could not access fsobj\n");
        }

        if(S_ISDIR(tempStat.st_mode))
        {
            //check execute
            Node* execute = exPermissions(realPath);
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = execute;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&execute, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //check write
            Node* write = writePermissions(realPath);
            //execute is on the insde because it is the limiter
            if (execute != NULL)
            {
                Node* temp1 = write;
                while (temp1 != NULL)
                {
                    Node* temp2 = execute;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&write, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on if not already
            Node* temp = write;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&write, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&write);
                printList(write);
            }
            freeList(execute);
            freeList(write);
        }
        else // is file or device
        {
            //check write
            Node* write = writePermissions(realPath);
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = write;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&write, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on if not already
            Node* temp = write;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&write, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&write);
                printList(write);
            }
            freeList(write);
        }
    }
    else if (!strcmp(action, "delete"))
    {
        struct stat parentStat;

        //parent directory
        if (stat(result, &parentStat) == -1)
        {
            fprintf(stderr,"Stat could not access fsobj\n");
            return 1;
        }

        //without sticky
        if (!(parentStat.st_mode & S_ISVTX))
        {
            //check execute
            Node* execute = exPermissions(result);
            //possible is on the insde because it is the limiter
            if (possible != NULL)
            {
                Node* temp1 = execute;
                while (temp1 != NULL)
                {
                    Node* temp2 = possible;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&execute, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //check write
            Node* write = writePermissions(result);
            //execute is on the insde because it is the limiter
            if (execute != NULL)
            {
                Node* temp1 = write;
                while (temp1 != NULL)
                {
                    Node* temp2 = execute;
                    int found = 0;
                    while (temp2 != NULL)
                    {
                        if (!strcmp(temp1->name,temp2->name))
                        {
                            found = 1;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (!found)
                    {
                        //points to next node by return value
                        temp1 = deleteNode(&write, temp1);
                        everyone = 0;
                    }
                    else
                        temp1 = temp1->next;
                }
            }

            //push root on if not already
            Node* temp = write;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&write, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&write);
                printList(write);
            }
            freeList(execute);
            freeList(write);
        }
        else // sticky
        {
            struct passwd *user = getpwuid(parentStat.st_uid);
            Node* writeParent = writePermissions(result);
            Node* list = NULL;
            Node* temp = writeParent;

            while (temp != NULL)
            {
                if (strcmp(temp->name,user->pw_name))
                {
                    push_back(&list, user->pw_name);
                    break;
                }
                else
                {
                    temp = temp->next;
                    everyone = 0;
                }
            }

            struct stat tempStat;
            //parent directory
            if (stat(realPath, &tempStat) == -1)
            {
                fprintf(stderr,"Stat could not access fsobj\n");
                return 1;
            }

            user = getpwuid(tempStat.st_uid);

            temp = writeParent;
            while (temp != NULL)
            {
                if (strcmp(temp->name,user->pw_name))
                {
                    push_back(&list, user->pw_name);
                    break;
                }
                else
                {
                    temp = temp->next;
                    everyone = 0;
                }
            }

            freeList(writeParent);

            //push root on if not already
            temp = list;
            int found = 0;
            while (temp != NULL)
            {
                if (!strcmp(temp->name,"root"))
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
            {
                push_back(&list, "root");
            }

            //print list
            if (everyone)
            {
                printf("everyone\n");
            }
            else
            {
                bubbleSort(&list);
                printList(list);
            }
            freeList(list);
        }
    }
    else
    {
        fprintf(stderr, "Invalid command line argument action: %s\n", action);
    }

    freeList(possible);
}

static Node* readPermissions(char* path)
{
    struct stat tempStat;

    if (stat(path, &tempStat) == -1)
    {
        fprintf(stderr,"Stat could not read file path\n");
        return NULL;
    }

    struct passwd *user = getpwuid(tempStat.st_uid);
    struct group *group = getgrgid(tempStat.st_gid);

    if (user == NULL || group == NULL)
    {
        fprintf(stderr,"Failed to get user or group in path");
        return NULL;
    }

    Node* head = NULL;

    //does the user have read
    if (tempStat.st_mode & S_IRUSR)
        push_back(&head, user->pw_name);
    else
        everyone = 0;

    //does the group have read
    if (tempStat.st_mode & S_IRGRP)
    {
        char **members = group->gr_mem;
        while (*members != NULL)
        {
            if (strcmp(user->pw_name, *members))
                push_back(&head, *members);
            members++;
        }
    }
    else
        everyone = 0;

    //do others have read
    if (tempStat.st_mode & S_IROTH)
    {
        struct passwd *others;
        setpwent();  // Rewind the passwd database to start reading from the beginning

        //first check user, if not, check group
        while ((others = getpwent()) != NULL)
        {
            if (strcmp(others->pw_name, user->pw_name) != 0)     // check if the username matches owner
                if (others->pw_gid != tempStat.st_gid)              // Check if the user's GID matches the group GID
                    push_back(&head, others->pw_name);
        }
        endpwent();
    }
    else
        everyone = 0;

    return head;
}

static Node* writePermissions(char* path)
{
    struct stat tempStat;

    if (stat(path, &tempStat) == -1)
    {
        fprintf(stderr,"Stat could not read file path\n");
        return NULL;
    }

    struct passwd *user = getpwuid(tempStat.st_uid);
    struct group *group = getgrgid(tempStat.st_gid);

    if (user == NULL || group == NULL)
    {
        fprintf(stderr,"Failed to get user or group in path");
        return NULL;
    }

    Node* head = NULL;

    //does the user have write
    if (tempStat.st_mode & S_IWUSR)
        push_back(&head, user->pw_name);
    else
        everyone = 0;

    //does the group have write
    if (tempStat.st_mode & S_IWGRP)
    {
        char **members = group->gr_mem;
        while (*members != NULL)
        {
            if (strcmp(user->pw_name, *members))
                push_back(&head, *members);
            members++;
        }
    }
    else
        everyone = 0;

    //do others have write
    if (tempStat.st_mode & S_IWOTH)
    {
        struct passwd *others;
        setpwent();  // Rewind the passwd database to start reading from the beginning

        //first check user, if not, check group
        while ((others = getpwent()) != NULL)
        {
            if (strcmp(others->pw_name, user->pw_name) != 0)     // check if the username matches owner
                if (others->pw_gid != tempStat.st_gid)              // Check if the user's GID matches the group GID
                    push_back(&head, others->pw_name);
        }
        endpwent();
    }
    else
        everyone = 0;

    return head;
}

static Node* exPermissions(char* path)
{
    struct stat tempStat;

    if (stat(path, &tempStat) == -1)
    {
        fprintf(stderr,"Stat could not read file path\n");
        return NULL;
    }

    struct passwd *user = getpwuid(tempStat.st_uid);
    struct group *group = getgrgid(tempStat.st_gid);

    if (user == NULL || group == NULL)
    {
        fprintf(stderr,"Failed to get user or group in path");
        return NULL;
    }

    Node* head = NULL;

    //does the user have ex
    if (tempStat.st_mode & S_IXUSR)
        push_back(&head, user->pw_name);
    else
        everyone = 0;

    //does the group have ex
    if (tempStat.st_mode & S_IXGRP)
    {
        char **members = group->gr_mem;
        while (*members != NULL)
        {
            if (strcmp(user->pw_name, *members))
                push_back(&head, *members);
            members++;
        }
    }
    else
        everyone = 0;

    //do others have ex
    if (tempStat.st_mode & S_IXOTH)
    {
        struct passwd *others;
        setpwent();  // Rewind the passwd database to start reading from the beginning

        //first check user, if not, check group
        while ((others = getpwent()) != NULL)
        {
            if (strcmp(others->pw_name, user->pw_name) != 0)     // check if the username matches owner
                if (others->pw_gid != tempStat.st_gid)              // Check if the user's GID matches the group GID
                    push_back(&head, others->pw_name);
        }
        endpwent();
    }
    else
        everyone = 0;

    return head;
}

static Node* permToRoot(const char* path)
{
    char* lastSlash;
    if (path == NULL)
    {
        fprintf(stderr, "Path is NULL\n");
        return NULL;
    }
    else
    {
        lastSlash = strrchr(path, '/');
    }

    Node* prevHead = NULL;

    if (lastSlash == NULL)
    {
        return NULL;
    }
    else if (lastSlash != path)
    {
        size_t len = lastSlash - path;
        char result[len + 1];  // +1 for the null terminator
        strncpy(result, path, len);
        result[len] = '\0';

        prevHead = permToRoot(result);

        if (prevHead == NULL)
        {
            return NULL;
        }
    }
    else if (lastSlash == path && strcmp(path, "/\0"))
    {
        prevHead = permToRoot("/\0");

        if (prevHead == NULL)
            return NULL;
    }

    struct stat tempStat;

    if (stat(path, &tempStat) == -1)
    {
        fprintf(stderr,"Stat could not read file path\n");
        return NULL;
    }

    if (S_ISREG(tempStat.st_mode))
        return prevHead;

    struct passwd *user = getpwuid(tempStat.st_uid);
    struct group *group = getgrgid(tempStat.st_gid);

    if (user == NULL || group == NULL)
    {
        fprintf(stderr,"Failed to get user or group in path");
        return NULL;
    }

    Node* head = NULL;

    //does the user have ex
    if (tempStat.st_mode & S_IXUSR)
        push_back(&head, user->pw_name);
    else
        everyone = 0;

    //does the group have ex
    if (tempStat.st_mode & S_IXGRP)
    {
        char **members = group->gr_mem;
        while (*members != NULL)
        {
            if (strcmp(user->pw_name, *members))
                push_back(&head, *members);
            members++;
        }
    }
    else
        everyone = 0;

    //do others have ex
    if (tempStat.st_mode & S_IXOTH)
    {
        struct passwd *others;
        setpwent();  // Rewind the passwd database to start reading from the beginning

        //first check user, if not, check group
        while ((others = getpwent()) != NULL)
        {
            if (strcmp(others->pw_name, user->pw_name) != 0)     // check if the username matches owner
                if (others->pw_gid != tempStat.st_gid)              // Check if the user's GID matches the group GID
                    push_back(&head, others->pw_name);
        }
        endpwent();
    }
    else
        everyone = 0;

    if (prevHead != NULL)
    {
        Node* temp1 = head;
        while (temp1 != NULL)
        {
            Node* temp2 = prevHead;
            int found = 0;
            while (temp2 != NULL)
            {
                if (!strcmp(temp1->name,temp2->name))
                {
                    found = 1;
                    break;
                }
                temp2 = temp2->next;
            }
            if (!found)
            {
                //points to next node by return value
                temp1 = deleteNode(&head, temp1);
            }
            else
                temp1 = temp1->next;
        }

        freeList(prevHead);
    }

    return head;
}
