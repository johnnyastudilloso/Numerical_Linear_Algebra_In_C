#include <stdlib.h>
#include <stdio.h>

/* Memory operations */
void open_file(FILE **file);
void **malloc_matrix(int m, int n, size_t size);
void *malloc_vector(int n, size_t size);
void free_matrix(void **matrix, int m);

/* Calculation operations */
float prod_esc(int n, double *a, double*b);
void prodMatVec(int m, int n, double **a, double *x, double *r);
double **prodMatMat(int m, int n, int k, double **a, double **b);
int resoltrisup(int m, int n, double **a, double *x, double tol);
void residu(int m, int n, double **a, double *x, double *r);
int elimgauss(int m, int n, double **a, double tol);
int elimgausspiv(int m, int n, double **a, double tol);
