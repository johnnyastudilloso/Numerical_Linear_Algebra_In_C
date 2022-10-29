#include <stdlib.h>
#include <stdio.h>

void prodMatVec(int m, int n, double **a, double *x, double *r)
{
    int i, j;
    double sum;

    for(i = 0; i < m; i++)
    {
        sum = 0;
        for(j = 0; j < n; j++)
        {
            sum += a[i][j] * x[j];
        }
        r[i] = sum;
    }
}
