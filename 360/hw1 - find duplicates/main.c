#include "linkedlist.h"
#include <stdio.h>

off_t get_file_size(const char *file_path);

void traverse_directory(const char *path);

int readFile(const char *path);

int main(int argc, char* argv[])
{
    // Check if command-line arguments are provided, otherwise use current directory
    if (argc < 2)
    {
        argv[1] = ".";
        argc = 2;
    }

    // Traverse all directories or files provided on the command line
    for (int i = 1; i < argc; i++)
    {
        traverse_directory(argv[i]);
    }

    printf("Files in list:\n");
    printList();
    printf("Duplicates:\n");
    findDuplicates();
    printDuplicates();

    freeList();

    return 0;
}


off_t get_file_size(const char *file_path)
{
    struct stat statbuf;
    if (stat(file_path, &statbuf) != 0)
    {
        perror(file_path);
        return -1;
    }
    return statbuf.st_size;
}

void traverse_directory(const char *path)
{
    struct stat path_stat;

    // Check if the path is a file or directory
    if (stat(path, &path_stat) == -1)
    {
        printf("Error checking the file or directory %s\n", path);
        return;
    }

    // If it's a file, get its size and insert it
    if (S_ISREG(path_stat.st_mode))  // Check if it's a regular file
    {
        readFile(path);
    }
    else if (S_ISDIR(path_stat.st_mode))  // It's a directory
    {
        // Try to open the directory
        DIR *dir = opendir(path);
        if (dir == NULL)
        {
            printf("Couldn't open %s as a directory\n", path);
            return;
        }

        struct dirent *entry;

        // Read the directory entries
        while ((entry = readdir(dir)) != NULL)
        {
            // are we skipping all '.' directories?
            /*if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;*/
            if (entry->d_name[0] == '.')
                continue;

            // Create full path for the file or subdirectory
            char file_path[MAX_PATH];
            snprintf(file_path, sizeof(file_path), "%s/%s", path, entry->d_name);

            // Recursively traverse the subdirectory or file
            traverse_directory(file_path);
        }

        closedir(dir);  // Close the directory when done
    }
    else  // If it's neither a file nor a directory, handle as an error or invalid path
    {
        printf("The path %s is neither a file nor a directory.\n", path);
    }
}

int readFile(const char *path)
{
    off_t size = get_file_size(path);
    if (size == -1)
    {
        printf("Couldn't get size of %s\n", path);
        return -1;
    }

    push_back(path, size);

    return 0;
}
