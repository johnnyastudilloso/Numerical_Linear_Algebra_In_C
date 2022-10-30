#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.c"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int main(void)
{
    /* Main variables */
    int i, j, s;
    double tol;

    /* File */
    FILE *file;
    char file_name[20];

    /* Matrix */
    double **ab, **u, **l, **c;
    double max;
    int m, n, k;

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
    printf("\nIntroduce el numero de filas de A: ");
    s = fscanf(file, "%d", &m);
    printf("%d", m);
    printf("\nIntroduce el numero de columnas de A: ");
    s = fscanf(file, "%d", &n);
    printf("%d", n);

    k = MIN(m, n);

    /* Reservamos memoria para la matriz  ampliada A|B */
    ab = (double **) malloc(m * sizeof(double *));
    if(ab == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz A");
        return 2;
    }

    for(i = 0; i < m; i++)
    {
        ab[i] = (double *) malloc(n * sizeof(double));
        if(ab[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz A");
            return 2;
        }
    }

    /* Reservamos memoria para la matriz  ampliada A|B */
    u = (double **) malloc(k * sizeof(double *));
    if(u == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz A");
        return 3;
    }

    for(i = 0; i < k; i++)
    {
        u[i] = (double *) malloc(n * sizeof(double));
        if(u[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz U");
            return 3;
        }
    }

    /* Reservamos memoria para la matriz  ampliada A|B */
    l = (double **) malloc(m * sizeof(double *));
    if(l == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz A");
        return 4;
    }

    for(i = 0; i < m; i++)
    {
        l[i] = (double *) malloc(k * sizeof(double));
        if(l[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz L");
            return 4;
        }
    }

    c = (double **) malloc(m * sizeof(double *));
    if(c == NULL)
    {
        printf("\nNo hay suficiente espacio en memoria para la matriz C");
        return 2;
    }

    for(i = 0; i < m; i++)
    {
        c[i] = (double *) malloc(n * sizeof(double));
        if(c[i] == NULL)
        {
            printf("\nNo hay suficiente espacio en memoria para la matriz C");
            return 2;
        }
    }

    /* Llenamos la matriz y la mostramos */
    printf("\n\nMatriz A:");

    for(i = 0; i < m; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            s = fscanf(file, "%lf", &ab[i][j]);
            printf("%.15lf ", ab[i][j]);
        }
        printf("]");
    }

    printf("\n\nTolerancia: ");
    s = fscanf(file, "%lf", &tol);
    printf("%e", tol);

    fclose(file);

    /* Aplicamos la eliminación gaussiana al sistema */
    printf("\n\n- Aplicando eliminación Gaussiana -\n\nMatriz A:");
    elimgauss(m, n, ab, tol);

    /* Mostramos la matriz ampliada*/
    for(i = 0; i < m; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            printf("%lf ", ab[i][j]);
        }
        printf("]");
    }

    /* Montamos la matriz L */
    for(i = 0; i < m; i++)
    {
        for(j = i; j < k; j++)
        {
            l[i][j] = 0;
        }
        l[i][i] = 1;
    }

    /* Mostramos la matriz L */
    for(i = m - 1; i >= 0; i--)
    {
        for(j = i - 1; j >= 0; j--)
        {
            l[i][j] = ab[i][j];
        }
    }

    printf("\n\n Matriz L:");
    for(i = 0; i < m; i++)
    {
        printf("\n[ ");
        for(j = 0; j < k; j++)
        {
            printf("%lf ", l[i][j]);
        }
        printf("]");
    }

    /* Montamos la matriz U */
    for(i = 0; i < k; i++)
    {
        for(j = i; j < n; j++)
        {
            u[i][j] = ab[i][j];
        }
    }

    printf("\n\n Matriz U:");
    for(i = 0; i < k; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            printf("%lf ", u[i][j]);
        }
        printf("]");
    }

    c = prodMatMat(m, n, k, l, u);

    printf("\n\nMatriz LU:");
    for(i = 0; i < m; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            printf("%lf ", c[i][j]);
        }
        printf("]");
    }

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            c[i][j] = ab[i][j] - c[i][j];
        }
    }

    printf("\n\nMatriz R:");
    for(i = 0; i < m; i++)
    {
        printf("\n[ ");
        for(j = 0; j < n; j++)
        {
            printf("%lf ", c[i][j]);
        }
        printf("]");
    }

    /* Calculo de la norma infinita */
    max = abs(c[0][0]);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(max < abs(c[i][j]))
                max = abs(c[i][j]);
        }
    }

    printf("\n\nNorma infinita de A - LU:\n%lf", max);

    for(i = 0; i < m; i++)
    {
        free(ab[i]);
    }
    free(ab);

    return 0;
}
