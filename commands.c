#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// A type for pointers to our command functions:
typedef void (*Command_function)(const char *);

// An association of a name with a function pointer:
struct Command_pair {
    const char *name;
    Command_function func;
};

// Prototypes for our command functions defined below:
void help_command(const char*);
void echo_command(const char*);
void exit_command(const char*);

// Our table of commands.
// A simple array is good enough for this use case.
// If the number of entries were large...
//      We'd want to qsort them and use bsearch to search them.
//      Or use something like a hashtable or red-black tree.
// We use a {NULL, NULL} entry to mark the end of the table.
struct Command_pair commands[] = {
    { "help", &help_command },
    { "echo", &echo_command },
    { "exit", &exit_command },
    { NULL, NULL }
};

// Given a name and argument, lookup the function pointer and call it:
void call_command(const char *name, const char *argument)
{
    for (int i = 0; commands[i].name != NULL; ++i) {
        if (0 == strcmp(commands[i].name, name)) {
            commands[i].func(argument);
            return;
        }
    }
    printf("Command not found\n");
}

// Our help command simply lists the available commands:
void help_command(const char* argument)
{
    printf("Commands are...\n");
    for (int i = 0; commands[i].name != NULL; ++i) {
        printf("\t%s\n", commands[i].name);
    }
}

// Echo prints its argument(s)
void echo_command(const char* argument)
{
    if (argument) printf("%s\n", argument);
    else printf("\n");
}

// Exit...exits!
void exit_command(const char* argument)
{
    exit(EXIT_SUCCESS);
}

int main()
{
    char *line = NULL;
    size_t size = 0;
    while (1) {
        // Print a prompt:
        printf("> ");
        fflush(stdout);
        // Read a line from the user:
        ssize_t length = getline(&line, &size, stdin);
        if (-1 == length) {
            // An error occurred.
            // Probably EOF, but in any case, we'll exit.
            printf("Whoops!\n");
            exit(EXIT_FAILURE);
        }
        // Replace the newline in the line with NUL
        line[length - 1] = '\0';
        // Strtok will parse the first token...the command name.
        // Note that it inserts a NUL in line at the end of the command name.
        char *command = strtok(line, " ");
        // NULL means strtok didn't find anything in line,
        // so we'll just ask the user for more input.
        if (!command) continue;
        // Strtok will now parse the next token from line.
        // If there isn't one, it'll return NULL,
        // and we'll just pass the NULL to the command.
        char *argument = strtok(NULL, " ");
        call_command(command, argument);
    }
    // Normally we'd want to free(line) at this point.
    // That's not necessary in this simple program where we'll just exit when we're done with line.
}
