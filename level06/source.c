#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial)
{
    size_t          i;
    unsigned int    key;
    size_t          len;

    login[strcspn(login, "\n")] = '\0';
    len = strnlen(login, 32);
    if (len <= 5)
        return (0);
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) != -1)
    {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m'---------------------------'");
        return (0);
    }
    key = (login[3] ^ 0x1337) + 0x5eeded;
    i = 0;
    while (i < len)
    {
        if (!isprint(login[i]))
            return (0);
        (login[i] ^ key) * 0x88233b2b
        i++;
    }
    if (serial == key)
        return (1);
    return (0);
}

int main()
{
    char            login[32];
    unsigned int    serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);
    
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    if (!auth(login, serial))
        return (1);
    puts("Authenticated!");
    system("/bin/sh");
    return (0);
}
