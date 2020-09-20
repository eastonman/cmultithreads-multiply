
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

// Traditional vertical calculation like algorithm, O(n^2)
/*
 * Input: 
 *   int *a, int *b: ptr to multicands
 *   int *c: ptr to result array
 *   int m, int n: length of mlticands
 * 
*/
void multiply(int *a, int *b, int *c, int m, int n)
{
    int i, j;

    // Multiply digit by digit
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            c[i + j] += a[i] * b[j];
        }
    }

    // Handles carries
    for (i = 0; i < n + m; i++)
    {
        if (c[i] >= 10)
        {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
}

void bigadd(int *a, int *b, int *c, int lengthA, int lengthB)
{
    int i;
    int carry = 0;

    // Copy A to C
    memcpy(c, a, lengthA * sizeof(int));

    // Add B to C digit by digit
    for (i = 0; i < lengthB; i++)
    {
        c[i] = (a[i] + b[i] + carry);
        carry = c[i] / 10;
        c[i] %= 10;
    }

    // Handles the last carry
    c[lengthB] += carry;
}

void bigsub(int *a, int *b, int *c, int lengthA, int lengthB)
{
    int i;

    // Copy a to c
    memcpy(c, a, lengthA * sizeof(int));

    // Substract digit by digit
    for (i = 0; i < lengthB; ++i)
    {
        c[i] = c[i] - b[i];
        if (c[i] < 0)
        {
            c[i + 1] -= 1;
            c[i] += 10;
        }
    }
    // Handles borrows
    for (i = lengthB; i < lengthA; ++i)
    {
        if (c[i] < 0)
        {
            c[i + 1] -= 1;
            c[i] += 10;
        }
    }
}

void bigjoin(int *var, int *result, int length)
{
    int i;
    int carry = 0;
    for (i = 0; i < length; ++i)
    {
        result[i] += var[i] + carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }

    // Handles the last carry
    result[length] += carry;
}