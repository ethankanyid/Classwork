#define _GNU_SOURCE // to get asprintf() prototype
#include <stdio.h>  // this needs to be the first #include in that case

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>

#include "except.h"

/*
 * Here's how you declare an exception with the "except" package:
 */
Except_T StatFailed = { "Failed to open file." };

Except_T TargetFound = { "Target Found." };

Except_T MiscellaneousError = { "Misc Error." };
/*
 * ASSIGNMENT
 *
 * Add additional declarations for exceptions TargetFound and
 * MiscellaneousError.
 */

char *progname = "*** progname not set ***"; /* should be argv[0] */

int verbose = 0; /* set on command line */

static void explore(char *path, char *target);

static void traverseDirectory(char path[], char *target)
{
    /*
    * ASSIGNMENT
    *
    * Implement the following pseudocode:
    *
    * open the directory associated with `path` (hint: opendir(3))
    * if the open fails,
    *     raise the MiscellaneousError exception
    * for each entry in the directory (hint: readdir(3)),
    *     if the entry's name is "."  or ".."
    *         skip that entry
    *     allocate a string `subpath` concatenatiing `path`, "/", and
    *      the entry's name (hint: asprintf())
    *     if in the following ... (hint: TRY ... END_TRY)
    *         call explore on `subpath` and pass `target` as well
    *     ... the TargetFound exception is raised (hint: EXCEPT())
    *         free `subpath`
    *         close the open directory (hint: closedir(3)
    *         re-raise the exception (hint: RERAISE)
    *     ... any other exception is raised (hint: ELSE)
    *         print a message to stderr that explore() failed
    *     free `subpath`
    * close the directory associated with `path` (hint: closedir(3))
    */

    DIR *dir = opendir(path);
    if (dir == NULL)
    RAISE (MiscellaneousError);

    struct dirent *entry;

    // Read the directory entries
    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, "."))
            continue;

        // Create full path for the file or subdirectory
        char file_path[4096];
        snprintf(file_path, sizeof(file_path), "%s/%s", path, entry->d_name);

        TRY
            explore(file_path, target);
        EXCEPT(StatFailed);
        EXCEPT(TargetFound)
        {
            closedir(dir);
            RERAISE;
        };
        ELSE
            fprintf(stderr, "explore() failed\n");
        END_TRY;

    }

    closedir(dir);
}


static void explore(char *path, char *target)
/* look at, in, and below `path` for a file named `target` */
{
    /*
     * ASSIGNMENT
     *
     * Implement the following pseudocode:
     *
     * get the status of `path` (hint: stat(2))
     * if it fails,
     *     raise the StatFailed exception (hint: RAISE)
     * find the last '/'-delimited component of `path` (or use `path`
     *  itself if it contains no '/'s, hint: strrchr())
     * if that component is equal to `target`, (hint: strcmp())
     *     if `verbose` is set,
     *         print `path` to standard output, followed by a newline
     *          (hint: printf())
     *     raise the TargetFound exception (hint: RAISE())
     * if `path` is a directory (hint: S_ISDIR())
     *     traverse it (hint: traverseDirectory())
     */

    struct stat path_stat;

    if (stat(path, &path_stat) == -1)
        RAISE (StatFailed);

    char *lastSlash = strrchr(path, '/');

    if (lastSlash != NULL && !strcmp(lastSlash + 1, target))
    {
        if (verbose)
            printf("Target Found: %s\n", path);
        RAISE(TargetFound);
    }
    if (S_ISDIR(path_stat.st_mode))
        traverseDirectory(path, target);
}

void findFile(char *top, char *target)
{
    /*
    * ASSIGNMENT
    *
    * Implement the following pseudocode:
    *
    * if in the following ... (hint: TRY ... END_TRY)
    *     call explore on `top` and pass `target` as well
    * ... the StatFailed exception is raised
    *     do nothing (put a ";" here)
    * ... the TargetFound exception is raised
    *     exit successfully (hint: exit(3))
    */
    TRY
        explore(top, target);
    EXCEPT (StatFailed);
    EXCEPT(TargetFound)
        exit(EXIT_SUCCESS);
    END_TRY;
}


void usage(void)
{
    printf("usage: %s [-h] [-v] target [directory]*\n", progname);
}


int main(int argc, char *argv[])
{
    int i, ch;
    char *target;
    extern int optind;

    progname = argv[0];
    while ((ch = getopt(argc, argv, "hv")) != -1) {
        switch (ch) {

        case 'v':
            verbose = 1;
            break;

        case 'h':
            usage();
            exit(EXIT_SUCCESS);

        case '?':
            usage();
            exit(EXIT_FAILURE);
        }
    }
    if (optind >= argc) {
        usage();
        exit(EXIT_FAILURE);
    }
    target = argv[optind++];
    if (optind == argc) {
        /* directory name(s) not provided */
        findFile(".", target);
    } else {
        /* directory name(s) provided */
        for (i = optind; i < argc; i++)
            findFile(argv[i], target);
    }
    /*
     * If we find the target, we'll exit immediately (and
     * successfully), so if we get to this point...
     */
    exit(EXIT_FAILURE);
}
