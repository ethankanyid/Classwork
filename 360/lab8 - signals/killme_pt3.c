#include <stdlib.h>    // for exit()
#include <stdio.h>     // for the usual printf(), etc.
#include <getopt.h>    // for getopt()
/*
* ASSIGNMENT
*
* - "#include" any other necessary headers (as indicated by "man"
*    pages)
*/
#include <errno.h>
#include "eprintf.h"
#include <string.h>
#include <signal.h>

/*
 * Note the new #include
 */
#include "critical_section.h"


// To get `getopt_long()` to work, you need to provide a static
// (usually) array of `struct option` structures.  There are four
// members to be filled in:

// 1. `name` is a (char *) string containing the "long" option name
// (e.g. "--help" or "--format=pdf").

// 2. `has_arg` has one of these values that describe the
// corresponding option:
enum {
    NO_ARG  = 0, // the option takes no argument
    REQ_ARG = 1, // the option must have an argument
    OPT_ARG = 2  // the option takes an optional argument
};

// 3. The "flag" is an int pointer that determines how the function
// will return its value. If it is NULL, getopt_long() will return
// "val" (the fourth member) as its function return. If it is not
// NULL, getopt_long() will return 0 and set "*flag" to "val".

// 4. "val" is an int which is either a character to denote a "short"
// (e.g. "-h" or "-f pdf") option or 0, to denote an option which does
// not have a "short" form.

// The array is terminated by an entry with a NULL name (first
// element).

static struct option options[] = {
    // elements are:
    // name       has_arg   flag   val
    { "children", OPT_ARG,  NULL,  'c'},
    { "help",     NO_ARG,   NULL,  'h'},
    { "nosync",   NO_ARG,   NULL,  'n'},
    { "pgid",     NO_ARG,   NULL,  'g'},
    { "ppid",     NO_ARG,   NULL,  'p'},
    { NULL }  // end of options table
};

/*
 * These globals are set by command line options. Here, they are set
 * to their default values.
 */
int showPpids = 0;   // show parent process IDs
int showPgids = 0;   // show process group IDs
int synchronize = 1; // synchronize outputs (don't use until Part 3)


enum { IN_PARENT = -1 }; // must be negative
/*
 * In the parent, this value is IN_PARENT. In the children, it's set
 * to the order in which they were spawned, starting at 0.
 */
int siblingIndex = IN_PARENT;


// This is a global count of signals received.
int signalCount = 0;


void writeLog(char message[], const char *fromWithin)
// print identifying information about the current process to stdout
{
    /*
    * ASSIGNMENT
    *
    * - Insert your previous writeLog() code here with this
    *   modification: If the global `synchronize` flag is set, call
    *   criticalSection_enter() before the first printf() call and
    *   criticalSection_leave() after the last one.
    */

    char processName[1024];
    int colonIndent = 0;

    if (siblingIndex == IN_PARENT)
    {
        strcpy(processName,"parent\0");
        colonIndent = 20;
    }
    else
    {
        snprintf(processName, 1024, "%s %d", "child", siblingIndex);
        colonIndent = 30;
    }

    if (synchronize)
    {
        criticalSection_enter();
    }

    printf("%*s: %s\n", colonIndent, "process name", processName);
    printf("%*s: %d\n", colonIndent, "pid", getpid());
    if (showPpids != 0)
        printf("%*s: %d\n",colonIndent, "ppid", getppid());
    if (showPgids != 0)
        printf("%*s: %d\n",colonIndent, "pgid", getpgrp());
    printf("%*s: %d\n",colonIndent, "signalCount", signalCount);
    printf("%*s: %s\n",colonIndent, "message", message);
    printf("%*s: %s\n",colonIndent, "fromWithin", fromWithin);
    printf("\n");

    if (synchronize)
    {
        criticalSection_leave();
    }
}


void inChild(int iSibling)
// do everything that's supposed to be done in the child
{
    /*
    * ASSIGNMENT
    *
    * - insert your previous inChild() code here unchanged
    */

    siblingIndex = iSibling;
    writeLog("pause()d", __func__);
    while (1)
    {
        pause();
    }
}


void handler(int sigNum)
// handle signal `sigNum`
{
    /*
    * ASSIGNMENT
    *
    * - insert your previous handler() code here unchanged
    */

    signalCount++;
    char buffer[1024];

    snprintf(buffer, 1024, "%d %s", sigNum, strsignal(sigNum));
    writeLog(buffer, __func__);
}


void initSignals(void)
// initialize all signals
{
    /*
    * ASSIGNMENT
    *
    * - insert your previous initSignals() code here unchanged
    */

    for (int i = 0; i < NSIG; i++)
    {
        if(i != SIGTRAP || i != SIGQUIT)
            if (signal(i, handler) == SIG_ERR)
            {
                char buffer[1024];

                snprintf(buffer, 1024, "%d %s", i, strsignal(i));
                writeLog(buffer, __func__);
            }
    }
}


void inParent(void)
// do everything that's supposed to be done in the parent
{
    /*
    * ASSIGNMENT
    *
    * - insert your previous inParent() code here unchanged
    */

    writeLog("Waiting for children to die", __func__);

    int status = 0;
    pid_t child_pid = 0;

    while ((child_pid = wait(&status)) != -1)
    {
        char msg[1024];
        if (WIFEXITED(status)) // normal exit
        {

            snprintf(msg, 1024, "Child PID %d exited normally with status %d.", child_pid, WEXITSTATUS(status));
            writeLog(msg, __func__);
        }
        else
        {
            writeLog("Child exited with an unknown abnormal status.", __func__);
        }
        if (WIFSIGNALED(status)) //was signaled
        {
            snprintf(msg, sizeof(msg), "Child PID %d was terminated by signal %d: %s.", child_pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
            writeLog(msg, __func__);
        }
    }


    if (errno == ECHILD)
    {
        writeLog("No children left to wait for.", __func__);
    }
    else
    {
        // Any other wait failure
        writeLog("wait() failed for an unknown reason.", __func__);
    }
}


static void usage(char *progname)
// issue a usage error message
{
    eprintf("usage: %s [{args}]*\n", progname);
    eprintf("%s\n", " {args} are:");
    eprintf("%s",
        "  -c[{arg}] or --children[={arg}]  fork {arg} children (default: 1)\n"
        "  -g or --pgid                     list process group IDs\n"
        "  -n or --nosync                   turn off synchronization\n"
        "  -p or --ppid                     list parent PIDs (default: no)\n"
        "  -h or --help                     help (this message) and exit\n"
        );
    return;
}

int main(int argc, char **argv)
{
    int ch;
    int nSiblings = 0;
    static char *progname = "**UNSET**";

    /*
     * Parse the command line arguments.
     */
    progname = argv[0];
    for (;;) {
        ch = getopt_long(argc, argv, "c::ghnp", options, NULL);
        if (ch == -1)
            break;

        switch (ch) {

        case 'c':
            if (optarg)
                nSiblings = atoi(optarg);
            else
                nSiblings = 1;
            break;

        case 'g':
            showPgids = 1;
            break;

        case 'h':
            usage(progname);
            exit(0);

        case 'n':
            synchronize = 0;
            break;

        case 'p':
            showPpids = 1;
            break;

        default:
            printf("?? getopt returned character code 0x%02x ??\n", ch);
            exit(1);
        }
    }
    /*
    * ASSIGNMENT
    *
    * - Insert your previous main() code here unchanged, except that
    *   if the global `synchronize` flag is set, add a call to
    *   criticalSection_init() before the initializeSignals() call.
    */

    if(synchronize)
        criticalSection_init();

    initSignals();
    if (nSiblings == 0)
    {
        writeLog("parent is pause()'d for a signal", __func__);
        while (1)
            pause();
    }
    else
    {
        for (int iSibling = 0; iSibling < nSiblings; iSibling++)
        {
            pid_t pid = fork();

            if (pid == -1) // Error handling if fork fails
            {
                perror("Fork failed");
            }
            else if (pid == 0) // in child
            {
                inChild(iSibling);
            }
            else if (pid > 0) // parent process logs child forking
            {
                char msg[1024];
                snprintf(msg, sizeof(msg), "Parent forked child %d with PID %d.", iSibling, pid);
                writeLog(msg, __func__);
            }
        }

        inParent();
    }

    return 0;
}
