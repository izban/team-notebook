
struct Simplex {
    ll a[MAX_M][MAX_N];
    ll b[MAX_M];
    ll c[MAX_N];
    ll v;    
    ll n, m;
    ll left[MAX_M];
    ll up[MAX_N];

    void init(ll nn, ll mm) {
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

    int pos[MAX_N];

    void pivot(ll x, ll y) {
        swap(left[x], up[y]); 
        ll k = a[x][y];
        assert(abs(k) == 1);
        a[x][y] = 1;
        b[x] /= k;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            a[x][i] = a[x][i] / k;
            if (a[x][i] != 0)
                pos[cur++] = i;
        }
        
        for (int i = 0; i < m; i++) {
            if (i == x || a[i][y] == 0) continue;
            ll cof = a[i][y];
            b[i] -= cof * b[x];
            a[i][y] = 0;
            for (int j = 0; j < cur; j++)
                a[i][pos[j]] -= cof * a[x][pos[j]];
        }
        ll cof = c[y];
        v += cof * b[x];
        c[y] = 0;
        for (int i = 0; i < cur; i++) {
            c[pos[i]] -= cof * a[x][pos[i]];
        }
    }

    ll res[MAX_N];
    void solve() {
        for (int i = 0; i < n; i++)
            up[i] = i;
        for (int i = 0; i < m; i++)
            left[i] = i + n;

        while (1) {
            int x = -1;
            for (int i = 0; i < m; i++)
                if (b[i] < 0 && (x == -1 || b[i] < b[x])) {
                    x = i;
                }
            if (x == -1) break;

            int y = -1;
            for (int j = 0; j < n; j++)
                if (a[x][j] < 0) {
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
                if (c[i] > 0  && (y == -1 || (c[i] > c[y]))) {
                    y = i;
                }
            if (y == -1) break;
            
            int x = -1;
            for (int i = 0; i < m; i++) {
                if (a[i][y] > 0) {
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
};


