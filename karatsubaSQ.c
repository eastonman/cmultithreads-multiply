#include <stdlib.h>
#include "mybig.c"

struct MyBig *karatsubaSQ(struct MyBig *a, struct MyBig *b)
{
    // Directlt return when any one is zero
    if (a->length == 0 || b->length == 0)
    {
        struct MyBig *zero = (struct MyBig *)malloc(sizeof(struct MyBig));
        *zero = (struct MyBig){NULL, 0};
        return zero;
    }

    // Use traditional multiply when number is small
    if (a->length <= 250 || b->length <= 250)
    {
        return myBigMultiply(a, b);
    }

    int half = (a->length > b->length ? a->length : b->length) / 2;

    struct MyBig *a1, *a2, *b1, *b2;
    if (a->length < half)
    {
        a1 = &(struct MyBig){NULL, 0};
        a2 = &(struct MyBig){a->ptr, a->length};
    }
    else
    {
        a1 = &(struct MyBig){a->ptr + half, a->length - half};
        a2 = &(struct MyBig){a->ptr, half};
    }

    if (b->length < half)
    {
        b1 = &(struct MyBig){NULL, 0};
        b2 = &(struct MyBig){b->ptr, b->length};
    }
    else
    {
        b1 = &(struct MyBig){b->ptr + half, b->length - half};
        b2 = &(struct MyBig){b->ptr, half};
    }

    struct MyBig *a1b1 = karatsubaSQ(a1, b1);
    struct MyBig *a2b2 = karatsubaSQ(a2, b2);
    struct MyBig *middle = karatsubaSQ(myBigAdd(a1, b1), myBigAdd(a2, b2));
    middle = myBigSub(myBigSub(middle, a1b1), a2b2);
    struct MyBig *result = myBigAdd(a2b2, myBigAdd(myBigPow(a1b1, 2 * half), myBigPow(middle, half)));
    return result;
}