namespace retro
{
    const int N = 4e5 + 10;

    vi v[N];
    vi vrev[N];

    void add(int x, int y)
    {
        v[x].pb(y);
        vrev[y].pb(x);
    }

    int res[N];
    int moves[N];
    int deg[N], used[N];
    int q[N], st, en;

    void calc(int n)
    {
        forn(i, n) res[i] = -1, deg[i] = sz(v[i]), moves[i] = inf;
        st = en = 0;
        forn(i, n) if (!deg[i])
        {
            res[i] = 0;
            q[en++] = i;
            moves[i] = 0;
        }
        while (st < en)
        {
            int x = q[st++];
            for (int y : vrev[x])
            {
                moves[y] = min(moves[y], moves[x] + 1);
                res[y] = 1;
                if (!used[y])
                {
                    used[y] = 1;
                    for (int z : vrev[y])
                    {
                        deg[z]--;
                        if (!deg[z])
                        {
                            res[z] = 0;
                            q[en++] = z;
                            moves[z] = moves[y] + 1;
                        }
                    }
                }
            }
        }
    }
}
