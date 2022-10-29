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
