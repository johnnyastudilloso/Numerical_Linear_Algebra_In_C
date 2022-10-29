#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../dependences/prodMatVec.c"
#include "../dependences/prod_escalar.c"
#include "../dependences/linalg.c"

int main(void)
{
    int i, j, m, n, k;
    double **a,*x, *r;
    double tol = 0;
    double norma;

    /* Fichero */
    char file_name[20];
    FILE *entrada;

    /* Abrimos el fichero */
    printf("Introduce el nombre del fichero:\n");
    scanf("%s", file_name);

    entrada = fopen(file_name, "r");

    if(entrada == NULL)
    {
        printf (" Error al abrir el fitxer %s\n" , file_name);
        return 1;
    }

    /*Solicitamos las dimensiones de la matriz y el vector */
    k = fscanf(entrada, "%d", &m);
    printf("\nFilas: %d", m);
    k = fscanf(entrada, "%d", &n);
    printf("\nColumnas: %d", n);

    /* Reservamos esapcio para la matriz y los vectores necesarios */
    /* Matriz */
    a = (double **) malloc(m * sizeof(double *));
    if(a == NULL)
    {
        printf("No hay espacio suficiente en memoria para la matriz");
        return 2;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = (double *) malloc(n * sizeof(double));
        if(a[i] == NULL)
        {
            printf("No hay espacio suficiente en memoria para la matriz");
            return 3;
        }
    }

    /* Vector de resultados */
    x = (double *) malloc(m * sizeof(double));
    if(x == NULL)
    {
        printf("No hay espacio suficiente en memoria para el vector de resultados");
        return 4;
    }

    /* Vector residuo */
    r = (double *) malloc(m * sizeof(double));
    if(r == NULL)
    {
        printf("No hay espacio suficiente en memoria para el vector residuo");
        return 5;
    }

    /* Llenamos la matriz */

    for(i = 0; i < m; i++)
    {
        printf("\nLeyendo fila nº %d:\n", i);
        printf("-----------------------------------------\n");
        for(j = 0; j < n; j++)
        {
            printf("\nLeyendo columna nº %d: ", j);
            k = fscanf(entrada, "%lf", &a[i][j]);
            printf("%.15f ", a[i][j]);
        }
    }

    /* Mostramos la matriz creada */
    printf("\n\nMatriz creada:\n");
    printf("----------------");
    for(i = 0; i < m; i++)
    {
        printf("\n");
        for(j = 0; j < n; j++)
        {
            printf(" %lf", a[i][j]);
        }
    }

    /* Leemos la tolerancia */
    printf("\n\nIntroduce el valor de la tolerancia: ");
    k = fscanf(entrada, "%lf", &tol);
    printf("%e", tol);

    fclose(entrada);

    /* Resolvemos la matriz */
    k = resoltrisup(m, n, a, x, tol);

    if(!k)
    {
        /* Mostramos la solución */
        printf("\n\nSOLUCIÓN: ");
        printf("[ ");
        for(i = 0; i < m; i++)
        {
            printf("%lf ", x[i]);
        }
        printf("]\n");

        residu(m, n, a, x, r);

        /* Calculo de la norma 2 del resiudo */
        printf("\nNorma 2 del residuo: ");

        norma = prod_esc(m, r, r);
        norma = sqrt(norma);

        printf("%lf\n\n", norma);
    }

    /* Liberamos el espacio de la memoria dinamica */
    free(x);
    free(r);

    for(i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);

    return 0;
}
