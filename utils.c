#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void benchmark(void (*work)(int *a, int *b, int *c, int n, int m),
               int *a, int *b, int *c, int n, int m)
{
    struct timespec start, stop;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    work(a, b, c, n, m);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    double duration = (double)(stop.tv_sec - start.tv_sec + (stop.tv_nsec, start.tv_nsec) / 1000000000.0);
    printf("Costs time: %f\n", duration);

    return;
}

void writeResult(int *c, int lengthC)
{
    int j;
    // Find out first non-zero digit
    for (j = lengthC - 1; j > 0; j--)
    {
        if (c[j] != 0)
            break;
    }

    // Do output
    FILE *output = NULL;
    output = fopen("./output.txt", "a+");
    int i;
    for (i = j; i >= 0; i--)
    {
        fprintf(output, "%d", c[i]);
    }
    fprintf(output, "\n");
    fclose(output);
}

void writeBigResult(unsigned long *c, int lengthC)
{
    int j;
    // Find out first non-zero digit
    for (j = lengthC - 1; j > 0; j--)
    {
        if (c[j] != 0)
            break;
    }

    // Do output
    FILE *output = NULL;
    output = fopen("./output.txt", "a+");
    int i;
    for (i = j; i >= 0; i--)
    {
        fprintf(output, "%d", c[i]);
    }
    fprintf(output, "\n");
    fclose(output);
}