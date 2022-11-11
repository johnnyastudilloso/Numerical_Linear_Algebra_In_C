/* Memory operations */
void open_file(FILE **file)
{
    char file_name[20];

    /* Opening */
    printf(" File name > ");
    scanf("%s", file_name);

    *file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("¡Error loading file!\n");
        exit(1);
    }
}

void **malloc_matrix(int m, int n, size_t size)
{
    int i, j;
    
    void **matrix;

    /* Reservamos esapcio para la matriz y los vectores necesarios */
    matrix = (void **) malloc(m * sizeof(void *));
    if(matrix == NULL)
    {
        printf("¡Not enough memory for the matrix!");
        return ((void **) 1);
    }

    for(i = 0; i < m; i++)
    {
        matrix[i] = (void *) malloc(n * size);
        if(matrix[i] == NULL)
        {
            printf("¡Not enough memory for the matrix!");
            return ((void **) 2);
        }
    }
    return matrix;
}

void *malloc_vector(int n, size_t size)
{
    void *vector;

    vector = (void *) malloc(n * size);
    if(vector == NULL)
    {
        printf("¡Not enough memory for the vector!");
        return ((void *) 1);
    }

    return vector;
}

void free_matrix(void **matrix, int m)
{
    int i;

    for(i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
}

/* Calculation orpeations */

float prod_esc(int n, double *a, double*b)
{
    int i;
    float prod = 0.f;

    for(i = 0; i < n; i++)
    {
        prod += a[i] * b[i];
    }

    return prod;
}

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

double **prodMatMat(int m, int n, int k, double **a, double **b)
{
    int i, j, p;
    double sum;
    double **c;

    c = (double **) malloc(m * sizeof(double *));
    if(c == NULL)
    {
        printf("No hay espacio en memoria para la matriz C");
        return NULL;
    }

    for(i = 0; i < k; i++)
    {
        c[i] = (double *) malloc(n * sizeof(double));
        if(c[i] == NULL)
        {
            printf("No hay espacio en memoria para la matriz C");
            return NULL;
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            sum = 0;
            for(p = 0; p < k; p++)
            {
                sum += a[j][p] * b[p][i];
            }
            c[j][i] = sum;
        }
    }
    return c;
}

/*
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
        printf("\nInvalid dimensions of the matrix:\nn = m + 1");
        return 1;
    }
    for(i = 0; i < m; i++)
    {
        if(fabs(a[i][i]) < tol)
        {
            printf("\na[%d][%d]: %f < tolerance: %f", i, i, a[i][i], tol);
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
    double *ax;

    ax = malloc_vector(n, sizeof(double));

    prodMatVec(m, n, a, x, ax);

    printf("\nVector Ax: [ ");
    for(i = 0; i < m; i++)
    {
        printf("%lf ", ax[i]);
    }
    printf("]\n");

    /* Restamos */
    printf("\nVector residuo: [ ");
    for(i = 0; i < m; i++)
    {
        r[i] = a[i][n - 1] - ax[i];
        printf("%lf ", r[i]);
    }
    printf("]\n");
}

int elimgauss(int m, int n, double **a, double tol)
{
    int i, j, k;
    double factor;

    for(i = 0; i < m; i++)
    {
        for(j = i + 1; j < m; j++)
        {
            factor = a[j][i] / a[i][i];
            for(k = i; k < n; k++)
            {
                a[j][k] = a[j][k] - factor * a[i][k];
            }
            a[j][i] = factor;
        }
    }

    return 0;
}


int elimgausspiv(int m, int n, double **a, double tol)
{
    int i, j, k, max;
    double factor;
    double temp[n];

    for(i = 0; i < m; i++)
    {
        max = i;
        for(j = i + 1; j < m; j++)
        {
            if(fabs(a[j][i]) > fabs(a[max][i]))
                max = i;
        }

        for(j = i; j < n; j++)
        {
            temp[j] = a[i][j];
            a[i][j] = a[max][j];
            a[max][j] = temp[j];
        }

        for(j = i + 1; j < m; j++)
        {
            factor = a[j][i] / a[i][i];
            for(k = i; k < n; k++)
            {
                a[j][k] -= factor * a[i][k];
            }
            a[j][i] = factor;
        }
    }

    return 0;
}
