/**
 * Resolvemos una matriz a mediante substitución hacia atrás
 */
int resoltrisup(int m, int n, double **a, double *x, double tol)
{
    /* Variables de recorrido */
    int i, j;
    double sum;

    /* Comprobamos que las dimensiones de la matriz sean correctas */
    if(n != m + 1)
    {
        printf("\nNumero de filas y columnas incorrecto:\nn = m + 1");
        return 1;
    }
    for(i = 0; i < m; i++)
    {
        if(fabs(a[i][i]) < tol)
        {
            printf("\na[%d][%d]: %f < tolerancia: %f", i, i, a[i][i], tol);
            return 1;
        }
    }
    /* Guardamos el resultado de la primera ecución (resolución directa) */
    x[m - 1] = a[m - 1][n - 1]/a[m - 1][m - 1];

    /* Resolvemos el resto de equaciones en funcion de la inicial de forma iterativa */
    for(i = m - 2; i >= 0; i--)
    {
        sum = 0;
        for (j = m - 1; j > i; j--)
        {
            sum += a[i][j] * x[j];
        }
        x[i] = (a[i][n - 1] - (sum)) / a[i][i];
    }
    return 0;
}

/* Esta funcion calcula el vector residuo de un sistema lineal */
void residu(int m, int n, double **a, double *x, double *r)
{
    int i;

    prodMatVec(m, n, a, x, r);

    printf("\nVector Ax: [ ");
    for(i = 0; i < m; i++)
    {
        printf("%lf ", r[i]);
    }
    printf("]\n");

    /* Mostramos los terminos independientes */
    printf("\nTerminos independientes: [ ");

    for(i = 0; i < m; i++)
    {
        printf("%lf ", a[i][n - 1]);
    }
    printf("]\n");

    /* Restamos */
    printf("\nVector residuo: [ ");
    for(i = 0; i < m; i++)
    {
        r[i] = a[i][n - 1] - r[i];
        printf("%lf ", r[i]);
    }
    printf("]\n");
}

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
