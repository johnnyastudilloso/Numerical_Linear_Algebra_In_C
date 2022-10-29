#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <../Ejercicio1/linalg.c>

int main(void)
{
    /* Main variables */
    int i, j, k;
    double tol;

    /* File */
    FILE *file;
    char file_name[20];

    /* Matrix */
    double **a, *b, *x;
    int n;

    /* Abrimos el fichero */
    printf("\nIntroduce el nombre del fichero: ");
    scanf("%s", file_name);

    file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("\nError al abrir el fichero: %s", file_name);
        return 1;
    }

    /* Solicitamos las dimensiones de la matriz y el vector */
    printf("\nIntroduce las dimensiones de la matriz A (n x n): ");
    k = fscanf(file, "%d", &n);
    printf("%d", n);

    /* Reservamos memoria para la matriz */
    a = (double **) malloc(n * sizeof(double *));
    if(a == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz A");
        return 2;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = (double *) malloc(n * sizeof(double));
        if(a[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz A");
            return 2;
        }
    }

    /* Reservamos espacio en memoria para el vector b */
    b = (double *) malloc(n * sizeof(double));
    if(b == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para el vector b");
        return 3;
    }

    /* Reservamos espacio para el vector x */
    x = (double *) malloc(n * sizeof(double));
    if(x == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para el vecto x");
        return 4;
    }

    /* Llenamos la matriz y la mostramos */
    printf("\n\nMatriz A:");

    for(i = 0; i < n; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            k = fscanf(file, "%lf", &a[i][j]);
            printf("%.15lf ", a[i][j]);
        }
        printf("]");
    }

    printf("\n\nVector b:\n[ ");
    for(i = 0; i < n; i++)
    {
        k = fscanf(file, "%lf", &b[i]);
        printf("%lf ", b[i]);
    }
    printf("]");

    printf("\n\nTolerancia: ");
    k = fscanf(file, "%lf", &tol);
    printf("%lf", tol);

    flcose(file);

    /* Aplicamos la eliminación gaussiana al sistema */
    printf("\n\n- Aplicando eliminación Gaussiana -\nMatriz A:");
    elimgauss(n, n + 1, a, tol);

    /* Mostramos la matriz */
    for(i = 0; i < n; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            printf("%lf ", a[i][j]);
        }
        printf("]");
    }

    printf("\n\n- Resolviendo sistema -");
    resoltrisup(n, n + 1, a, x, tol);

    /* Mostramos el vector x */
    printf("\n\nVector x:\n[ ")
    for(i = 0; i < n; i++)
    {
        printf("%lf ", x[i]);
    }
    printf("]");

    free(b);

    for(i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);

    return 0;
}
