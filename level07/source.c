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

unsigned int get_unum(void)
{
    unsigned int nb;

    fflush(stdout);
    scanf("%u", &nb);
    return (nb);
}

int store_number(unsigned int *mem)
{
    unsigned int nb;
    unsigned int idx;

    printf(" Number: ");
    nb = get_unum();
    printf(" Index: ");
    idx = get_unum();
    if ((idx % 3 == 0) || (idx >> 0x18 == 0xb7))
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return (0);
    }
    *(mem + (idx << 2)) = nb;
    return (1);
}

int read_number(unsigned int *mem)
{
    unsigned int idx;

    printf(" Index: ");
    idx = get_unum();
    printf(" Number at data[%u] is %u\n", idx, mem[idx]);
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
    unsigned int    memory[100];
    int             status;
    char            cmd[20];

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
        else
            status = 0;

        if (status)
            printf(" Completed %s command successfully\n", cmd);
        else
            printf(" Failed to do %s command\n", cmd);

        bzero(cmd, 20);
    }
}
