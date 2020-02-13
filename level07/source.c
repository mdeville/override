#include <stdio.h>
#include <string.h>
#include <strings.h>

const char prompt[] =   "----------------------------------------------------\n"
                        "  Welcome to wil's crappy number storage service!   \n"
                        "----------------------------------------------------\n"
                        " Commands:                                          \n"
                        "    store - store a number into the data storage    \n"
                        "    read  - read a number from the data storage     \n"
                        "    quit  - exit the program                        \n"
                        "----------------------------------------------------\n"
                        "   wil has reserved some storage :>                 \n"
                        "----------------------------------------------------\n";

int get_unum(void)
{

}

int store_number(char *mem)
{
    printf(" Number: ");

}

int read_number(char *mem)
{
    return (1);
}

static inline void clear(char **p)
{
    while (*p)
    {
        bzero(*p, strlen(*p));
        p++;
    }
}

int main(int argc, char **argv, char **envp)
{
    char    memory[400];
    int     status;
    char    cmd[20];

    bzero(cmd, 20);
    bzero(memory, 400);

    // clears args and env
    clear(argv);
    clear(envp);

    puts(prompt);
    while (1) {
        printf("Input command: ");
        fgets(cmd, 20, stdin);
        cmd[strlen(cmd) - 1] = '\0';
        
        if (strcmp(cmd, "store") == 0)
            status = store_number(memory);
        else if (strcmp(cmd, "read") == 0)
            status = read_number(memory);
        else if (strcmp(cmd, "quit") == 0)
            return (0);

        if (status)
            printf(" Completed %s command successfully\n", cmd);
        else
            printf(" Failed to do %s command\n", cmd);

        bzero(cmd, 20);
    }
}
