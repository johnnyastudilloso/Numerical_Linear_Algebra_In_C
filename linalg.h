float prod_esc(int n, double *a, double*b);
void prodMatVec(int m, int n, double **a, double *x, double *r);
int resoltrisup(int m, int n, double **a, double *x, double tol);
void residu(int m, int n, double **a, double *x, double *r);
int elimgauss(int m, int n, double **a, double tol);
int elimgausspiv(int m, int n, double **a, double tol);
double metode_potencia(int n, double **a, double *x0, double tol);