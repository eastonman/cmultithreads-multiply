#include <string.h>

struct MyBig
{
    unsigned long *ptr;
    unsigned length;
};

struct MyBig *myBigMultiply(struct MyBig *a, struct MyBig *b)
{
    int i, j;

    unsigned long int *c = malloc((a->length + b->length + 1) * sizeof(unsigned long));
    memset(c, 0, (a->length + b->length + 1) * sizeof(unsigned long int));

    // Multiply digit by digit
    for (i = 0; i < a->length; i++)
    {
        for (j = 0; j < b->length; j++)
        {
            c[i + j] += a->ptr[i] * b->ptr[j];
        }
    }

    // Handles carries
    for (i = 0; i < a->length + b->length; i++)
    {
        if (c[i] >= 10)
        {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    struct MyBig *result = malloc(sizeof(struct MyBig));
    *result = (struct MyBig){c, a->length + b->length + 1};
    return result;
}

struct MyBig *myBigAdd(struct MyBig *a, struct MyBig *b)
{
    int i;
    int carry = 0;

    unsigned int lengthC = a->length > b->length ? a->length + 1 : b->length + 1;
    unsigned long int *c = malloc(lengthC * sizeof(unsigned long));
    memset(c, 0, (lengthC) * sizeof(unsigned long int));

    // Copy A to C
    memcpy(c, a->ptr, a->length * sizeof(unsigned long int));

    // Add B to C digit by digit
    for (i = 0; i < b->length; i++)
    {
        c[i] += b->ptr[i] + carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }

    // Handles the last carry
    c[b->length] += carry;

    struct MyBig *result = malloc(sizeof(struct MyBig));
    *result = (struct MyBig){c, lengthC};
    return result;
}

struct MyBig *myBigSub(struct MyBig *a, struct MyBig *b)
{
    int i;
    unsigned int lengthC = a->length > b->length ? a->length : b->length;
    unsigned long int *c = malloc(lengthC * sizeof(unsigned long));
    memset(c, 0, (lengthC) * sizeof(unsigned long int));

    // Copy a to c
    memcpy(c, a->ptr, a->length * sizeof(unsigned long));

    int borrow = 0;
    // Substract digit by digit
    for (i = 0; i < b->length; ++i)
    {

        if (c[i] < b->ptr[i] + borrow)
        {
            c[i] += 10 - b->ptr[i] - borrow;
            borrow = 1;
        }
        else
        {
            c[i] -= b->ptr[i] + borrow;
            borrow = 0;
        }
    }

    struct MyBig *result = malloc(sizeof(struct MyBig));
    *result = (struct MyBig){c, lengthC};

    return result;
}

struct MyBig *myBigPow(struct MyBig *a, int expo)
{
    unsigned long length = a->length + expo;
    unsigned long *c = malloc(length * sizeof(unsigned long));
    memset(c, 0, length * sizeof(unsigned long));
    memcpy(c + expo, a->ptr, a->length * sizeof(unsigned long));

    struct MyBig *result = malloc(sizeof(struct MyBig));
    *result = (struct MyBig){c, length};
    return result;
}