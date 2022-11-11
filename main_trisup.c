#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.c"

int main(void)
{
    int i, j, k;
    char file_name[20];
    
    /* Matrix atributes */
    int m, n;
    double tol;
    double norma;
    double **a, *x, *r;

    /* File */
    FILE *file;

    open_file(&file);

    /* Solicitamos las dimensiones de la matriz y el vector */
    printf("\nRows > ");
    k = fscanf(file, "%d", &m);
    printf("%d\n", m);

    printf("\nColumns > ");
    k = fscanf(file, "%d", &n);
    printf("%d\n", n);

    a = (double **) malloc_matrix(m, n, sizeof(double));
    x = (double *) malloc_vector(m, sizeof(double));
    r = (double *) malloc_vector(m, sizeof(double));

    /* Llenamos la matriz y la mostramos */
    printf("\nMatrix A:\n");

    for(i = 0; i < m; i++)
    {
        printf("[ ");
        for(j = 0; j < n; j++)
        {
            k = fscanf(file, "%lf", &a[i][j]);
            printf("%.15f ", a[i][j]);
        }
        printf("]\n");
    }

    /* Leemos la tolerancia */
    printf("\nTolerance > ");
    k = fscanf(file, "%lf", &tol);
    printf("%e\n", tol);

    fclose(file);

    /* Resolvemos la matriz */
    k = resoltrisup(m, n, a, x, tol);

    if(!k)
    {
        /* Mostramos la solución */
        printf("\nSOLUTION: ");
        printf("[ ");
        for(i = 0; i < m; i++)
        {
            printf("%lf ", x[i]);
        }
        printf("]\n");

        residu(m, n, a, x, r);

        /* Calculo de la norma 2 del resiudo */
        printf("\nNorm 2 of the residual vector: ");

        norma = prod_esc(m, r, r);
        norma = sqrt(norma);

        printf("%lf\n\n", norma);
    }

    /* Liberamos el espacio de la memoria dinamica */
    free(x);
    free(r);

    free_matrix((void **) a, m);

    return 0;
}
