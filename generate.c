#include "stdio.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    FILE *output = NULL;
    int length = 0;
    scanf("%d", &length);
    output = fopen("./input.txt", "w+");
    int i, a;
    srand((unsigned)time(NULL));

    // First number
    for (int i = 0; i < length; i++)
    {
        a = rand() % 10;
        fputc(a + '0', output);
    }
    fprintf(output, "\n");
    srand((unsigned)time(NULL) + a * a);

    // Second Number
    for (int i = 0; i < length; i++)
    {
        a = rand() % 10;
        fputc(a + '0', output);
    }

    fclose(output);
    return 0;
}
