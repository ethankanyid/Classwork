#include "snapshot.h"

#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/resource.h>
//#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PATH 1024

int moveFile(char* source, char* destination);

/*  generate a ”snapshot” tarball of a running program suitable for debugging */
int snapshot(char *ssname, char *progpath, char *readme)
{
    pid_t pid = getpid();
    struct stat st = {0};

    // Check if directory already exists
        if (stat(ssname, &st) == 0)
        {
            fprintf(stderr, "Error: Directory %s already exists.\n", ssname);
            return -1;
        }

    // Create snapshot directory 755 for no write in group and other
        if (mkdir(ssname, 0755) == -1)
        {
            perror("mkdir failed");
            return -1;
        }

    // Write README.txt
        char readmefile[MAX_PATH];
        snprintf(readmefile, sizeof(readmefile), "%s/README.txt", ssname);
        FILE *fp = fopen(readmefile, "w");
        if (!fp)
        {
            perror("fopen README failed");
            return -1;
        }
        fprintf(fp, "%s\n", readme);
        fclose(fp);

    // Set unlimited core dump size
        struct rlimit rl = {RLIM_INFINITY, RLIM_INFINITY};
        if (setrlimit(RLIMIT_CORE, &rl) == -1)
        {
            perror("Setrlimit failed");
            return -1;
        }

    // Create core dump
        pid_t child = fork();
        pid_t childPID = 0;

        if(child == 0) // child block
        {
            abort(); //force core dump
        }
        else if (child > 0) //parent block
        {
            childPID = child;
            int status = 0;
            waitpid(child, &status, 0); //waits for child to exit and gives status
        }
        else
        {
            perror("Fork failed");
        }

        char coreFileSrc[MAX_PATH];
        char coreFileDes[MAX_PATH];
        snprintf(coreFileDes, sizeof(coreFileDes), "%s/core.%d", ssname,pid);
        snprintf(coreFileSrc, sizeof(coreFileSrc), "core.%d", childPID); //uses childs pid
        if (moveFile(coreFileSrc,coreFileDes) == -1)
        {
            perror("Failed to move core dump");
        }

    // Copy the executable
        char exePathSrc[MAX_PATH];
        char exePathDes[MAX_PATH];
        snprintf(exePathSrc, sizeof(exePathSrc), "/proc/%d/exe", pid);
        snprintf(exePathDes, sizeof(exePathDes), "%s/%s", ssname, basename(progpath));

        if (moveFile(exePathSrc,exePathDes) == -1)
        {
            perror("Failed to move executable");
        }

    // Create tarball
        char tarfile[MAX_PATH];
        snprintf(tarfile, sizeof(tarfile), "%s.tgz", ssname);
        char tar[2048];
        snprintf(tar, sizeof(tar), "tar -czf %s %s", tarfile, ssname);
        if (system(tar) == -1)
        {
            perror("tar");
            return -1;
        }

    // Remove snapshot directory and files
        unlink(readmefile);
        unlink(exePathDes);
        unlink(coreFileDes);
        unlink(coreFileSrc);
        rmdir(ssname);

    return 0;
}

int moveFile(char* source, char* destination)
{
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1)
    {
        fprintf(stderr,"Failed to open source: %s\n",source);
        return -1;
    }

    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (dest_fd == -1) {
        fprintf(stderr,"Failed to open destination: %s\n",destination);
        close(src_fd);
        return -1;
    }

    char buf[4096];
    ssize_t bytes;
    while ((bytes = read(src_fd, buf, sizeof(buf))) > 0) {
        if (write(dest_fd, buf, bytes) != bytes) {
            fprintf(stderr,"Failed to write to destination: %s\n",destination);
            close(src_fd);
            close(dest_fd);
            return -1;
        }
    }
    close(src_fd);
    close(dest_fd);

    return 0;
}
