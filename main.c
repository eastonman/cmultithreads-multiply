#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include "arithmetic.c"
#include "karatsuba.c"
#include "utils.c"

#define MAX_LENGTH 150000

void newMultiply(int *a, int *b, int *c, int m, int n);

int main()
{
    // Get multicands
    FILE *input = NULL;
    input = fopen("./input.txt", "r+");
    char numberN[MAX_LENGTH], numberM[MAX_LENGTH];
    fscanf(input, "%s%s", numberN, numberM);
    fclose(input);

    // Turn multicands for char array to int array
    int n = strlen(numberN), m = strlen(numberM);
    int a[MAX_LENGTH], b[MAX_LENGTH];
    int i, j;
    for (i = 0, j = n - 1; i < n; i++, j--)
    {
        a[i] = numberN[j] - '0';
    }
    for (i = 0, j = m - 1; i < m; i++, j--)
    {
        b[i] = numberM[j] - '0';
    }

    // Initial result array
    int lengthC = m + n + 1;
    int c[lengthC];
    memset(c, 0, lengthC * sizeof(int));

    // Clear output.txt
    FILE *output = NULL;
    output = fopen("./output.txt", "w+");
    fclose(output);

    // Run Multiply
    /*benchmark(&multiply, a, b, c, n, m);

    writeResult(c, lengthC);

    // Reset c
    memset(c, 0, lengthC * sizeof(int));*/

    // Run MultiProcessing Multiply
    /*benchmark(&newMultiply, a, b, c, n, m);
    writeResult(c, lengthC);

    // Reset c
    memset(c, 0, lengthC * sizeof(int));*/

    /*benchmark(&multiplyMP, a, b, c, n, m);
    writeResult(c, lengthC);

    // Reset c
    memset(c, 0, lengthC * sizeof(int));*/

    unsigned long inputC[n],
        inputD[m];
    for (i = 0, j = n - 1; i < n; i++, j--)
    {
        inputC[i] = numberN[j] - '0';
    }
    for (i = 0, j = m - 1; i < m; i++, j--)
    {
        inputD[i] = numberM[j] - '0';
    }
    struct MyBig *BigA = &(struct MyBig){inputC, n};
    struct MyBig *BigB = &(struct MyBig){inputD, m};

    struct timespec start, stop;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    struct MyBig *BigResult = karatsubaSQ(BigA, BigB);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    double duration = (double)(stop.tv_sec - start.tv_sec + (stop.tv_nsec, start.tv_nsec) / 1000000000.0);
    printf("Costs time: %f\n", duration);

    writeBigResult(BigResult->ptr, BigResult->length);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    BigResult = karatsubaPL(BigA, BigB);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    duration = (double)(stop.tv_sec - start.tv_sec + (stop.tv_nsec, start.tv_nsec) / 1000000000.0);
    printf("Costs time: %f\n", duration);

    writeBigResult(BigResult->ptr, BigResult->length);

    return 0;
}

struct para
{
    int *a;
    int *b;
    int *c;
    int n;
    int m;
};

void *worker(void *arg)
{
    struct para *p = (struct para *)arg;
    multiply(p->a,
             p->b,
             p->c,
             p->n,
             p->m);
    //printf("%s\n","Done");
}

// Toom-Cook 2-way algorithm with 3 threads
/*
 * Input: 
 *   int *a, int *b: ptr to multicands
 *   int *c: ptr to result array
 *   int m, int n: length of mlticands
 * 
*/
void newMultiply(int *a, int *b, int *c, int lengthA, int lengthB)
{
    // Avoid handling small numbers
    /*if (!((lengthA <= 50) || (lengthB <= 50)))
    {
        multiply(a, b, c, lengthA, lengthB);
        return;
    }*/

    // Threads
    pthread_t ids[4];
    int i;

    // Split
    // a: a1a2
    // b: b1b2
    // a * b = a1b1 * 10^x
    //   + a2b2
    //   + (a1b2+a2b1) * 10^x/2
    // needs to calculate
    // a1b1,a2b2,(a1+b1)*(a2+b2)
    int half = max(lengthA, lengthB) / 2;

    // Initial result array
    int lengthA1B1 = lengthA + lengthB - 2 * half;
    int a1b1[lengthA1B1];
    memset(a1b1, 0, (lengthA1B1) * sizeof(int));

    int lengthA2B2 = 2 * half;
    int a2b2[lengthA2B2];
    memset(a2b2, 0, (lengthA2B2) * sizeof(int));

    int lengthMiddle = 2 * half + 2;
    int middle[lengthMiddle];
    memset(middle, 0, (lengthMiddle) * sizeof(int));
    int middle2[lengthMiddle];
    memset(middle2, 0, (lengthMiddle) * sizeof(int));

    // calculate
    struct para arg = {a + half, b + half, a1b1, lengthA - half, lengthB - half};
    pthread_create(&ids[0], NULL,
                   worker,
                   &arg);
    //multiply(a + half, b + half, a1b1, lengthA - half, lengthB - half);
    struct para arg2 = (struct para){a, b, a2b2, half, half};
    pthread_create(&ids[1], NULL,
                   worker,
                   &arg2);

    //multiply(a, b, a2b2, half, half);

    // Initial (a1+b1) and (a2+b2)
    int temp1[max(lengthA - half, lengthB - half) + 1];
    int temp2[half + 1];
    memset(temp1, 0, (max(lengthA - half, lengthB - half) + 1) * sizeof(int));
    memset(temp2, 0, (half + 1) * sizeof(int));
    bigadd(a + half, b + half, temp1, lengthA - half, lengthB - half);
    bigadd(a, b, temp2, half, half);

    arg = (struct para){temp1, temp2, middle, max(lengthA - half, lengthB - half) + 1, half + 1};
    pthread_create(&ids[2], NULL,
                   worker,
                   &arg);
    //multiply(temp1, temp2, middle, max(lengthA - half, lengthB - half) + 1, half + 1);

    for (i = 0; i < 3; ++i)
    {
        pthread_join(ids[i], NULL);
    }
    bigsub(middle, a1b1, middle2, lengthMiddle, lengthA1B1);
    bigsub(middle2, a2b2, middle, lengthMiddle, lengthA2B2);

    bigjoin(a2b2, c, lengthA2B2);
    bigjoin(a1b1, c + 2 * half, lengthA1B1);
    bigjoin(middle, c + half, lengthMiddle);
}