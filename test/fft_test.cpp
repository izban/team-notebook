//#pragma GCC optimize("O3") 
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx") 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dbl;
#define forn(i, n) for (int i = 0; i < (n); i++)
#define pw(k) (1LL<<(k))
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
const int MOD = 998244353;

namespace fft
{
    struct pt
    {
        dbl x, y;
        pt(){}
        pt(dbl xx, dbl yy): x(xx), y(yy) {}
    };

    pt operator + (pt a, pt b)
    {
        return pt(a.x + b.x, a.y + b.y);
    }
    pt operator - (pt a, pt b)
    {
        return pt(a.x - b.x, a.y - b.y);
    }

    pt operator * (pt a, pt b)
    {
        return pt(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    pt conj(pt z)
    {
        return pt(z.x, -z.y);
    }

    const int base = 20;
    const int N = 1 << base;

    pt root[N];
    int rev[N];

    void init()
    {
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
        int NN = N >> 1;
        forn(i, NN)
        {
            dbl alp = i * acos(-1) / NN;
            root[i + NN] = pt(cos(alp), sin(alp));
        }
        for (int i = NN - 1; i > 0; --i) root[i] = root[2 * i];
    }

    void fft(pt *a, pt *f)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
        {
            pt z = f[i + j + k] * root[j + k];
            f[i + j + k] = f[i + j] - z;
            f[i + j] = f[i + j] + z;
        }
    }

    ll A[N], B[N], C[N];
    pt a[N], b[N], f[N], g[N];

    void _mult(int mod, int eq)
    {
        forn(i, N)
        {
            int x = A[i] % mod;
            a[i] = pt(x & (pw(15) -1 ), x >> 15);
        }
        forn(i, N)
        {
            int x = B[i] % mod;
            b[i] = pt(x & (pw(15) -1 ), x >> 15);
        }
        fft(a, f);
        if (eq) forn(i, N) g[i] = f[i];
        else fft(b, g);
        forn(i, N)
        {
            int j = (N - i) & (N - 1);
            pt a1 = (f[i] + conj(f[j])) * pt(0.5, 0);
            pt a2 = (f[i] - conj(f[j])) * pt(0, -0.5);
            pt b1 = (g[i] + conj(g[j])) * pt(0.5 / N, 0);
            pt b2 = (g[i] - conj(g[j])) * pt(0, -0.5 / N);
            a[j] = a1 * b1 + a2 * b2 * pt(0, 1);
            b[j] = a1 * b2 + a2 * b1;
        }
        fft(a, f);
        fft(b, g);
        forn(i, N)
        {
            ll aa = f[i].x + 0.5;
            ll bb = g[i].x +0.5;
            ll cc = f[i].y + 0.5;
            C[i] = (aa + bb % mod * pw(15) + cc % mod * pw(30))% mod;
        }
    }
    void mult(int n1, int n2, int mod, int eq)
    {
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(mod, eq);

        //forn(i, n1 + n2) C[i] =0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * B[j]) % mod;
    }
}

int bin(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        n >>= 1;
    }
    return res;
}

int inv(int x) {
    return bin(x, MOD - 2);
}

namespace fft2
{
    const int base = 20;
    const int N = 1 << base;
    const int ROOT = 646;

    int root[2][N];
    int rev[N];

    void init()
    {
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
        int NN = N >> 1;
        for (int j = 0; j < 2; j++) {
            int croot = j ? inv(ROOT) : ROOT;
            int cur = 1;
            forn(i, NN)
            {
                root[j][i + NN] = cur;
                cur = 1LL * cur * croot % MOD;
            }
            for (int i = NN - 1; i > 0; --i) root[j][i] = root[j][2 * i];
        }
    }

    void fft(int *a, int *f, int _inv)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
        {
            int z = 1LL * f[i + j + k] * root[_inv][j + k] % MOD;
            f[i + j + k] = (f[i + j] - z + MOD) % MOD;
            f[i + j] = (f[i + j] + z) % MOD;
        }
        if (_inv) {
            int on = inv(N);
            for (int i = 0; i < N; i++) f[i] = 1LL * f[i] * on % MOD;
        }
    }

    int A[N], B[N], C[N];
    int f[N], g[N];

    void _mult(int mod, int eq)
    {
        fft(A, f, 0);
        fft(B, g, 0); 
        for (int i = 0; i < N; i++) f[i] = 1LL * f[i] * g[i] % MOD;
        fft(f, C, 1);
    }
    void mult(int n1, int n2, int mod, int eq)
    {
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(mod, eq);

        //forn(i, n1 + n2) C[i] =0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * B[j]) % mod;
    }
}

// from anta code http://codeforces.com/contest/755/submission/23864531

/*#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
    unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
    asm(
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (y)
    );
#else
    __asm {
        mov edx, dword ptr[xh];
        mov eax, dword ptr[xl];
        div dword ptr[y];
        mov dword ptr[d], eax;
        mov dword ptr[m], edx;
    };
#endif
    out_d = d; out_m = m;
}

 */
// have no idea what sse flags are really cool; list of some of them
// -- very good with bitsets


namespace fft3
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



double stamp() {
    return clock() / (double)CLOCKS_PER_SEC;
}

void print(vector<int> a) {
    for (int x : a) cout << x << " ";
    cout << endl;
}

vector<int> multiplySlow(vector<int> a, vector<int> b) {
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % MOD;  
        }
    } 
    return c;
}

vector<int> multiplyDouble(vector<int> a, vector<int> b) {
    for (int i = 0; i < (int)a.size(); i++) fft::A[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) fft::B[i] = b[i];
    fft::mult(a.size(), b.size(), MOD, 0);
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)c.size(); i++) c[i] = fft::C[i];
    return c;
}

vector<int> multiplyLong(vector<int> a, vector<int> b) {
    for (int i = 0; i < (int)a.size(); i++) fft2::A[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) fft2::B[i] = b[i];
    fft2::mult(a.size(), b.size(), MOD, 0);
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)c.size(); i++) c[i] = fft2::C[i];
    return c;
}
vector<int> multiplyLong2(vector<int> a, vector<int> b) {
    for (int i = 0; i < (int)a.size(); i++) fft3::A[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) fft3::B[i] = b[i];
    fft3::mult(a.size(), b.size());
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)c.size(); i++) c[i] = fft3::C[i];
    return c;
}

void testCorrectness() {
    int n = 5, m = 5;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) a[i] = rand() % MOD;
    for (int i = 0; i < m; i++) b[i] = rand() % MOD;
    //vector<int> a(2, 1), b(2, 1);

    vector<int> v1 = multiplySlow(a, b);
    vector<int> v2 = multiplyDouble(a, b);
    vector<int> v3 = multiplyLong(a, b);
    vector<int> v4 = multiplyLong2(a, b);
    print(v1);
    print(v2);
    print(v3);
    print(v4);
    assert(v1 == v2);
    assert(v1 == v3);
    assert(v1 == v4);
}

void testSpeed() {
    int n = 5e5;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % MOD;
        b[i] = rand() % MOD;
    }
    double st, fn;

    st = stamp();
    multiplyDouble(a, b);
    fn = stamp();
    cerr << "double: " << fn - st << endl;

    st = stamp();
    multiplyLong(a, b);
    fn = stamp();
    cerr << "long: " << fn - st << endl;

    st = stamp();
    multiplyLong2(a, b);
    fn = stamp();
    cerr << "long: " << fn - st << endl;

}

int main() {
    fft::init();
    fft2::init();
    fft3::init();
    //int x = 1;
    //while (!(bin(x, fft::N) == 1 && bin(x, fft::N / 2) != 1)) x++;
    //cerr << x << endl;

    testCorrectness();
    testSpeed();

    return 0;
}

