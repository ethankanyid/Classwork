#include "allocarray.h"
#include "syscall_check.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
* compute the buffer size from argv[] (hint: atoi(3))
* allocate a buffer of the given size bytes (hint: malloc(3))
* open the input file read-only (hint: open(2))
* open the output file write-only and with "truncate" and "create" flags set, making sure that permissions permit writing (hint: open(2))
* loop:
    attempt to read the given size bytes from the input file into the buffer (hint: read(2))
    if zero bytes were read,
        exit the loop (we're done reading)
    write however many bytes were read from the buffer to the output file (hint: write(2))
* free the buffer (hint: free(3))
* close the input file (hint: close(2))
* close the output file (hint: close(2))
*/

int main (int argc, char* argv[])
{

    if (argc != 4)
    {
        printf("Invalid amount of arguments");
        return -1;
    }

    int bufferSize = atoi(argv[1]);
    char* buffer = malloc(sizeof(char) * bufferSize);
    if (buffer == 0)
    {
        printf("Failed to allocate bytes");
        return -1;
    }


    int in = open(argv[2], O_RDONLY);
    SYSCALL_CHECK(in);

    int out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    SYSCALL_CHECK(out);

    ssize_t reading = 0;
    ssize_t writing = 0;

    for (;;)
    {
        SYSCALL_CHECK(reading = read(in, buffer, bufferSize));

        if(reading == 0)
        {
            break;
        }

        SYSCALL_CHECK(writing = write(out, buffer, reading));
    }

    close(in);
    close(out);

    free(buffer);

    return 0;
}
