namespace fft
{
    const int mod = 998244353;
    const int base = 20;
    const int N = 1 << base;
    const int ROOT = 646;

    int root[N];
    int rev[N];

    void init()
    {
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
        int NN = N >> 1;
        int z = 1;
        forn(i, NN)
        {
            root[i + NN] = z;
            z = z * (ll)ROOT % mod;
        }
        for (int i = NN - 1; i > 0; --i) root[i] = root[2 * i];
    }

    void fft(int *a, int *f)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
        {
            int z = f[i + j + k] * (ll)root[j + k] % mod;
            f[i + j + k] = (f[i + j] - z + mod) % mod;
            f[i + j] = (f[i + j] + z) % mod;
        }
    }

    int A[N], B[N], C[N];
    int F[N], G[N];

    void _mult(int eq)
    {
        fft(A, F);
        if (eq) forn(i, N) G[i] = F[i];
        else fft(B, G);
        int invN = inv(N);
        forn(i, N) A[i] = F[i] * (ll)G[i] % mod * invN % mod;
        reverse(A + 1, A + N);
        fft(A, C);
    }

    void mult(int n1, int n2, int eq = 0)
    {
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(eq);

        //forn(i, n1 + n2) C[i] = 0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * (ll)B[j]) % mod;
    }
}
