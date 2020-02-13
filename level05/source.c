#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char buf[100];
	int i = 0;

	fgets(buf, 100, stdin);
	i = 0;
	while (i < strlen(buf))
	{
		if (buf[i] >= 'A' && buf[i] <= 'Z')
			buf[i] = buf[i] ^ 0x20; // tolower
		i++;
	}
	printf(buf);
	exit(0);
}
