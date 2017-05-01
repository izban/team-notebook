
namespace simplex {
    dbl a[MAX_M][MAX_N];
    dbl b[MAX_M];
    dbl c[MAX_N];
    dbl v;    
    ll n, m;
    int left[MAX_M];
    int up[MAX_N];
    int pos[MAX_N];
    dbl res[MAX_N];

    void init(int nn, int mm) {
        n = nn;
        m = mm;
        v = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = 0;
        for (int i = 0; i < m; i++)
            b[i] = 0;
        for (int i = 0; i < n; i++)
            c[i] = 0;
    }

    void pivot(int x, int y) {
        swap(left[x], up[y]); 
        dbl k = a[x][y];
        a[x][y] = 1;
        b[x] /= k;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            a[x][i] = a[x][i] / k;
            if (!eq(a[x][i], 0))
                pos[cur++] = i;
        }
        
        for (int i = 0; i < m; i++) {
            if (i == x || eq(a[i][y], 0)) continue;
            dbl cof = a[i][y];
            b[i] -= cof * b[x];
            a[i][y] = 0;
            for (int j = 0; j < cur; j++)
                a[i][pos[j]] -= cof * a[x][pos[j]];
        }
        dbl cof = c[y];
        v += cof * b[x];
        c[y] = 0;
        for (int i = 0; i < cur; i++) {
            c[pos[i]] -= cof * a[x][pos[i]];
        }
    }

    void solve() {
        for (int i = 0; i < n; i++)
            up[i] = i;
        for (int i = 0; i < m; i++)
            left[i] = i + n;

        while (1) {
            int x = -1;
            for (int i = 0; i < m; i++)
                if (ls(b[i], 0) && (x == -1 || b[i] < b[x])) {
                    x = i;
                }
            if (x == -1) break;
            int y = -1;
            for (int j = 0; j < n; j++)
                if (ls(a[x][j], 0)) {
                    y = j; 
                    break;
                }
            if (y == -1) {
                assert(false); // no solution
            }
            pivot(x, y);
        }
        while (1) {
            int y = -1;
            for (int i = 0; i < n; i++)
                if (ls(0, c[i])  && (y == -1 || (c[i] > c[y]))) {
                    y = i;
                }
            if (y == -1) break;
            
            int x = -1;
            for (int i = 0; i < m; i++) {
                if (ls(0, a[i][y])) {
                    if (x == -1 || (b[i] / a[i][y] < b[x] / a[x][y])) {
                        x = i;
                    } 
                }
            }
            if (y == -1) {
                assert(false); // infinite solution
            }
            pivot(x, y);
        }

        memset(res, 0, sizeof(res));

        for (int i = 0; i < m; i++) {
            if (left[i] < n) {
                res[left[i]] = b[i];
            }
        } 
    }
    // HOW TO USE ::
    // -- call init(n, m)
    // -- call solve()
    // -- variables in "up" equals to zero 
    // -- variables in "left" equals to b
    // -- max: c * x
    // -- b[i] >= a[i] * x
    // -- answer in "v"
    // -- sertificate in "res"
};

