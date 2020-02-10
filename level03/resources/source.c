#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void test(int nb, int nb2)
{
    int tmp;

    tmp = nb2 - nb;
    if (tmp < 0x15)
    {
    }
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
