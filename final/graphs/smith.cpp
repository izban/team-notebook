const int N = 1e5 + 10;

struct graph
{
    int n;

    vi v[N];
    vi vrev[N];

    void read()
    {
        int m;
        scanf("%d%d", &n, &m);
        forn(i, m)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            --x, --y;
            v[x].pb(y);
            vrev[y].pb(x);
        }
    }

    int deg[N], cnt[N], used[N], f[N];
    int q[N], st, en;

    set<int> s[N];

    void calc()
    {
        forn(x, n) f[x] = -1, cnt[x] = 0;
        int val = 0;
        while (1)
        {
            st = en = 0;
            forn(x, n)
            {
                deg[x] = 0;
                used[x] = 0;
                for (int y : v[x]) if (f[y] == -1) deg[x]++;
            }
            forn(x, n) if (!deg[x] && f[x] == -1 && cnt[x] == val)
            {
                q[en++] = x;
                f[x] = val;
            }
            if (!en) break;
            while (st < en)
            {
                int x = q[st];
                st++;
                for (int y : vrev[x])
                {
                    if (used[y] == 0 && f[y] == -1)
                    {
                        used[y] = 1;
                        cnt[y]++;
                        for (int z : vrev[y])
                        {
                            deg[z]--;
                            if (f[z] == -1 && deg[z] == 0 && cnt[z] == val)
                            {
                                f[z] = val;
                                q[en++] = z;
                            }
                        }
                    }
                }
            }
            val++;
        }
        forn(x, n) eprintf("%d%c", f[x],  " \n"[x + 1 == n]);
        forn(x, n) if (f[x] == -1)
        {
            for (int y : v[x]) if (f[y] != -1) s[x].insert(f[y]);
        }
    }
} g1, g2;

string get(int x, int y)
{
    int f1 = g1.f[x], f2 = g2.f[y];
    if (f1 == -1 && f2 == -1) return "draw";
    if (f1 == -1) {
        if (g1.s[x].count(f2)) return "first";
        return "draw";
    }
    if (f2 == -1) {
        if (g2.s[y].count(f1)) return "first";
        return "draw";
    }
    if (f1 ^ f2) return "first";
    return "second";
}
