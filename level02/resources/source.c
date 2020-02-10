#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc, char **argv)
{
    char password[112];     //filename
    char pass[48];          //ptr
    char username[100];     //format
    FILE *stream;
    size_t ret;

    bzero(username, 13);
    bzero(pass, 6);
    bzero(password, 13);

    if ((stream = fopen("/home/users/level03/.pass", "r")) == NULL)
    {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }
    ret = fread(pass, 1, 41, stream);
    pass[strcspn(pass, "\n")] = '\0';
    if (ret != 41)
    {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(stream);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("--[ Password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = '\0';
    puts("*****************************************");
    if (strncmp(password, pass, 41) != 0)
    {
        printf(username);
        puts(" does not have access!");
        exit(1);
    }
    printf("Greetings, %s\n", username);
    system("/bin/sh");
    return (0);
}
