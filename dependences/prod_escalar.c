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
