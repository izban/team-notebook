namespace fft
{
    const int maxBase = 21;
    const int maxN = 1 << maxBase;

    struct num
    {
        dbl x, y;
        num(){}
        num(dbl xx, dbl yy): x(xx), y(yy) {}
        num(dbl alp): x(cos(alp)), y(sin(alp)) {}
    };

    inline num operator + (num a, num b) { return num(a.x + b.x, a.y + b.y); }
    inline num operator - (num a, num b) { return num(a.x - b.x, a.y - b.y); }
    inline num operator * (num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    inline num conj(num a) { return num(a.x, -a.y); }

    const dbl PI = acos(-1);

    num root[maxN];
    int rev[maxN];
    bool rootsPrepared = false;

    void prepRoots()
    {
        if (rootsPrepared) return;
        rootsPrepared = true;
        root[1] = num(1, 0);
        for (int k = 1; k < maxBase; ++k)
        {
            num x(2 * PI / pw(k + 1));
            for (int i = pw(k - 1); i < pw(k); ++i)
            {
                root[2 * i] = root[i];
                root[2 * i + 1] = root[i] * x;
            }
        } 
    }    

    int base, N;

    int lastRevN = -1;
    void prepRev()
    {
        if (lastRevN == N) return;
        lastRevN = N;
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    }

    void fft(num *a, num *f)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
        {
            num z = f[i + j + k] * root[j + k];
            f[i + j + k] = f[i + j] - z;
            f[i + j] = f[i + j] + z;
        }
    }

    num a[maxN], b[maxN], f[maxN], g[maxN];
    ll A[maxN], B[maxN], C[maxN];

    void _multMod(int mod)
    {
        forn(i, N)
        {
            int x = A[i] % mod;
            a[i] = num(x & (pw(15) - 1), x >> 15);
        }
        forn(i, N)
        {
            int x = B[i] % mod;
            b[i] = num(x & (pw(15) - 1), x >> 15);
        }
        fft(a, f);
        fft(b, g);

        forn(i, N)
        {
            int j = (N - i) & (N - 1);
            num a1 = (f[i] + conj(f[j])) * num(0.5, 0);
            num a2 = (f[i] - conj(f[j])) * num(0, -0.5);
            num b1 = (g[i] + conj(g[j])) * num(0.5 / N, 0);
            num b2 = (g[i] - conj(g[j])) * num(0, -0.5 / N);
            a[j] = a1 * b1 + a2 * b2 * num(0, 1);
            b[j] = a1 * b2 + a2 * b1;
        }
        
        fft(a, f);
        fft(b, g);

        forn(i, N)
        {
            ll aa = f[i].x + 0.5;
            ll bb = g[i].x + 0.5;
            ll cc = f[i].y + 0.5;
            C[i] = (aa + bb % mod * pw(15) + cc % mod * pw(30)) % mod;
        }
    }

    void prepAB(int n1, int n2)
    {
        base = 1;
        N = 2;
        while (N < n1 + n2) base++, N <<= 1;

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        prepRoots();
        prepRev();
    }

    void mult(int n1, int n2)
    {
        prepAB(n1, n2);
        forn(i, N) a[i] = num(A[i], B[i]);
        fft(a, f);
        forn(i, N)
        {
            int j = (N - i)  & (N - 1);
            a[i] = (f[j] * f[j] - conj(f[i] * f[i])) * num(0, -0.25 / N);
        }
        fft(a, f);
        forn(i, N) C[i] = (ll)round(f[i].x);
    }


    void multMod(int n1, int n2, int mod)
    {
        prepAB(n1, n2);
        _multMod(mod);
    }

    int D[maxN];

    void multLL(int n1, int n2)
    {
        prepAB(n1, n2);

        int mod1 = 1.5e9;
        int mod2 = mod1 + 1;

        _multMod(mod1);

        forn(i, N) D[i] = C[i];

        _multMod(mod2);

        forn(i, N)
        {
            C[i] = D[i] + (C[i] - D[i] + (ll)mod2) * (ll)mod1 % mod2 * mod1;
        }
    }
    // HOW TO USE ::
    // -- set correct maxBase
    // -- use mult(n1, n2), multMod(n1, n2, mod) and multLL(n1, n2)
    // -- input  : A[], B[]
    // -- output : C[]
}
