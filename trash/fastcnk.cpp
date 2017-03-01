namespace math
{
    const int N = 3e5 + 10;
    
    int fact[N];
    int revfact[N];

    int revx[N];

    void init()
    {
        fact[0] = 1;
        for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * (ll)i % mod;
        revfact[0] = revfact[1] = 1;
        revx[1] = 1;
        for (int i = 2; i < N; ++i)
        {
            int c = mod / i + 1;
            revx[i] = revx[c * i - mod] * (ll)c % mod;
            revfact[i] = revfact[i - 1] * (ll)revx[i] % mod;
        }
    }

    int cnk(int n, int k)
    {
        if (k < 0 || k > n) return 0;
        return fact[n] * (ll)revfact[n - k] % mod * revfact[k] % mod;
    }
}
