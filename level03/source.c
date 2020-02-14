#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void decrypt(int key)
{
	size_t		i;
	size_t		len;
	char		cypher[] = "Q}|u`sfg~sf{}|a3";

	len = strlen(cypher);
	i = 0;
	while (i < len)
	{
		cypher[i] = cypher[i] ^ key;
		i++;
	}
	if (strcmp(cypher, "Congratulations!") != 0)
		puts("\nInvalid Password");
	else
		system("/bin/sh");
}

void test(int input, int key)
{
    int tmp;

    tmp = key - input;
    if (tmp <= 21)
        decrypt(tmp);
	else
		decrypt(rand());
}

int main()
{
    int nb;

    srand(time(NULL));
    puts("***********************************");
    puts("*\x09\x09level03\x09\x09**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &nb);
    test(nb, 0x1337d00d);
    return (0);
}
