namespace flow
{
    const int maxn = 1e5 + 10;
    const int maxe = 2 * maxn;

    int head[maxn], next[maxe], to[maxe], f[maxe], ec = 1;
    int ST, EN, N = maxn;

    inline void setN(int n)
    {
        ST = n;
        EN = n + 1;
        N = n + 2;
    }

    inline void _add(int x, int y, int ff)
    {
        ++ec;
        to[ec] = y;
        next[ec] = head[x];
        head[x] = ec;
        f[ec] = ff;
    }

    inline int add(int x, int y, int ff)
    {
        _add(x, y, ff);
        _add(y, x, 0);
        return ec - 1;
    }

    void clear()
    {
        forn(i, N) head[i] = 0;
        ec = 1;
    }
             
    int d[maxn];
    int q[maxn], st = 0, en = 0;

    int bfs()
    {
        forn(i, N) d[i] = 1e9;
        st = 0, en = 0;
        d[ST] = 0;
        q[en++] = ST;
        while (st < en)
        {
            int x = q[st++];
            if (x == EN) return 1;
            for (int e = head[x]; e; e = next[e])
            {
                int y = to[e];
                if (d[y] == 1e9 && f[e])
                {
                    d[y] = d[x] + 1;
                    q[en++] = y;
                }
            }
        }
        return 0;
    }                    
        
    int pushed;
    int fst[maxn];
    
    int dfs(int x, int flow = 1e9)
    {
        if (x == EN)
        {
            pushed = flow;
            return 1;
        }
        for (; fst[x]; fst[x] = next[fst[x]])
        {
            int e = fst[x];
            int y = to[e];
            if (d[y] == d[x] + 1 && f[e] && dfs(y, min(f[e], flow)))
            {
                f[e] -= pushed;
                f[e ^ 1] += pushed;
                return 1;
            }
        }
        return 0;
    }


    ll calcFlow()
    {
        ll res = 0;
        while (bfs())
        {
            forn(i, N) fst[i] = head[i];
            while (dfs(ST))
            {
                res += pushed;
            }
        }
        return res;
    }          

    // HOW TO USE ::
    // -- set maxn and maxe (special for izban)
    // -- add adges using add(x, y, f), call setN(n)
    // -- run calcFlow
}
