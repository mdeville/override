#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

FILE **reloc_stdin = &stdin;

void    secret_backdoor(void)
{
    char buffer[128];

    fgets(buffer, 128, *reloc_stdin);
    system(buffer);
}

void    set_msg(char *s)
{
    char    msg[1024];

    bzero(msg, 1024);
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(msg, 1024, *reloc_stdin);
    strncpy(s, msg, *((size_t *)s + 180));
}

void    set_username(char *s)
{
    char    username[140];
    size_t  i;

    bzero(s, 128);
    puts(">: Enter your username");
    printf(">>: ");
    fgets(username, 128, *reloc_stdin);

    i = 0;
    while (i <= 40)
    {
        if (username[i] == '\0')
            break;
        s[i + 140] = username[i];
        i++;
    }
    printf(">: Welcome, %s", s + 140);
}

void    handle_msg(void)
{
    char buffer[180];

    bzero(buffer + 140, 40);
    set_username(buffer);
    set_msg(buffer);
    puts(">: Msg sent!");
}

const char prompt[] =   "--------------------------------------------\n"
                        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
                        "--------------------------------------------";

int     main(int argc, char **argv)
{
    puts(prompt);
    handle_msg();
    return (0);
}
