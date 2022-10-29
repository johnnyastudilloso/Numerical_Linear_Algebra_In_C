#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* #include <../Ejercicio1/linalg.c> */

/*
 * INPUT: m = rows, n = columns, a = matrix, tol = tolerance
 *
 * OUTPUT: 0 if solved, 1 if not could solve it
 */
int elimgauss(int m, int n, double **a, double tol)
{
    int i, j, k;
    float div;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < m - 1; j++)
        {
            if(j > i)
            {
                div = a[j][i] / a[i][i];
                for(k = 0; k < m; k++)
                {
                    a[j][k] = a[j][k] - div * a[i][k];
                }
            }
        }
    }
}

int main(void)
{
    /* Main variables */
    int i, j, k;
    double tol;

    /* File */
    FILE *file;
    char file_name[20];

    /* Matrix */
    double **a, *b;
    int n;

    printf("\nIntroduce el nombre del fichero: ");
    scanf("%s", file_name);

    file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("\nError al abrir el fichero: %s", file_name);
        return 1;
    }

    /*Solicitamos las dimensiones de la matriz y el vector */
    printf("\nIntroduce las dimensiones de la matriz (n x n): ");
    k = fscanf(file, "%d", &n);
    printf("%d", n);

    /* Reservamos memoria para la matriz */
    a = (double **) malloc(n * sizeof(double *));
    if(a == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz");
        return 2;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = (double *) malloc(n * sizeof(double));
        if(a[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz");
            return 2;
        }
    }

    /* Reservamos espacio en memoria para el vector */
    b = (double *) malloc(n * sizeof(double));
    if(b == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para el vector");
        return 3;
    }

    /* Llenamos la matriz */
    printf("\n\nLeyendo matriz...");

    for(i = 0; i < n; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            k = fscanf(file, "%lf", &a[i][j]);
            printf("%lf ", a[i][j]);
        }
        printf("]");
    }

    printf("\n\nLeyendo vector...\n[ ");
    for(i = 0; i < n; i++)
    {
        k = fscanf(file, "%lf", &b[i]);
        printf("%lf ", b[i]);
    }
    printf("]");

    printf("\n\nIntroduce el valor de la tolerancia: ");
    k = fscanf(file, "%lf", &tol);
    printf("%lf", tol);

    printf("\n\nAplicando eliminacion gaussiana...");
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
    return 0;
}
