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

    const int UD = 0;
    const int WIN = 1;
    const int LOSE = 2;

    int res[N];
    int moves[N];
    int deg[N];
    int q[N], st, en;

    void calc(int n)
    {
        forn(i, n) deg[i] = sz(v[i]);
        st = en = 0;
        forn(i, n) if (!deg[i])
        {
            q[en++] = i;
            res[i] = LOSE;
        }
        while (st < en)
        {
            int x = q[st++];
            for (int y : vrev[x])
            {
                if (res[y] == UD && (res[x] == LOSE || (--deg[y] == 0 && res[x] == WIN)))
                {
                    res[y] = 3 - res[x];
                    moves[y] = moves[x] + 1;
                    q[en++] = y;
                }
            }
        }
    }
}
