#include <string.h>
#include <stdio.h>
#include "hello.h"


void activate_new_feature() {
	printf("Activating new feature...\n");
	// This either will look blue when printed or just look like a bunch of weird text
	// if your terminal somehow doesn't support ANSI codes.
	printf("\x1b[36mNew Feature activated\x1b[0m\n");
}

int main(int argc, char** argv)
{
	activate_new_feature();

	char buffer[50];

    printf("What is your name?: ");

    if (fgets(buffer,sizeof(buffer),stdin) == NULL)
        return 0;

    int size = strlen(buffer);
    buffer[size - 1] = '\0';

    say_hello(buffer);
}
