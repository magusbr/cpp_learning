/* Convert this program to C++
* change to C++ io
* change to one line comments
* change defines of constants to const
* change array to vector<>
* inline any short function
*/

#include <stdio.h>
#define N 40

void hw1_sum_0(int*p, int n, int d[])
{
    int i;

    *p = 0;
    for(i = 0; i < n; ++i)
        *p = *p + d[i];
}

int hw1_main_0()
{
    int i;
    int accum = 0;
    int data[N];

    for(i = 0; i < N; ++i)
        data[i] = i;
    sum(&accum, N, data);

    printf("sum is %d\n", accum);

    return 0;
}

void hw1_sum_1(int*p, int n, int d[])
{
    int i;

    *p = 0;
    for(i = 0; i < n; ++i)
        *p = *p + d[i];
}

int hw1_main_1()
{
    int i;
    int accum = 0;
    int data[N];

    for(i = 0; i < N; ++i)
        data[i] = i;
    sum(&accum, N, data);

    printf("sum is %d\n", accum);

    return 0;
}
