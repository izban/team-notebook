namespace fft {
    const int MOD = 998244353;
    const int base = 20;
    const int N = 1 << base;
    const int ROOT = 646;

    int root[N];
    int rev[N];

    ll inv(ll a, ll m = MOD) {
        if (a == 0) return 0;
        return ((1 - inv(m % a, a) * m) / a + m) % m;
    }

    void init() {
        for (int i = 0; i < N; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
        int NN = N >> 1;
        int z = 1;
        for (int i = 0; i < NN; i++) {
            root[i + NN] = z;
            z = z * (ll)ROOT % MOD;
        }
        for (int i = NN - 1; i > 0; --i) root[i] = root[2 * i];
    }

    void fft(int *a, int *f) {
        for (int i = 0; i < N; i++) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < N; i += 2 * k) { 
                for (int j = 0; j < k; j++) {
                    int z = f[i + j + k] * (ll)root[j + k] % MOD;
                    f[i + j + k] = (f[i + j] - z + MOD) % MOD;
                    f[i + j] = (f[i + j] + z) % MOD;
                }
            }
        }
    }

    int A[N], B[N], C[N];
    int F[N], G[N];

    void _mult(int eq) {
        fft(A, F);
        if (eq)
            for (int i = 0; i < N; i++) 
                G[i] = F[i];
        else fft(B, G);
        int invN = inv(N);
        for (int i = 0; i < N; i++) A[i] = F[i] * (ll)G[i] % MOD * invN % MOD;
        reverse(A + 1, A + N);
        fft(A, C);
    }

    void mult(int n1, int n2, int eq = 0) {
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(eq);

        //forn(i, n1 + n2) C[i] = 0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * (ll)B[j]) % mod;
    }
}
