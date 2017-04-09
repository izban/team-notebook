namespace flow
{
    const int maxn = 2e5 + 10;
    const int maxe = 2 * maxn;

    int head[maxn], next[maxe], to[maxe], flow[maxe], cost[maxe], ec = 1;
    int ST, EN, N = maxn;

    inline void setN(int n)
    {
        ST = n;
        EN = n + 1;
        N = n + 2;
    }

    inline void _add(int x, int y, int f, int c)
    {
        ++ec;
        to[ec] = y;
        next[ec] = head[x];
        head[x] = ec;
        flow[ec] = f;
        cost[ec] = c;
    }

    inline int add(int x, int y, int f, int c)
    {
        _add(x, y, f, c);
        _add(y, x, 0, -c);
        return ec - 1;
    }

    void clear()
    {
        forn(i, N) head[i] = 0;
        ec = 1;
    }

    ll d[maxn], p[maxn];
    int last[maxn];
    int used[maxn];

    pair<ll, ll> _calc(int flag)
    {
        const ll INF = 1e12;
        forn(i, N) p[i] = INF;
        p[ST] = 0;
        forn(_, N) forn(x, N) for (int e = head[x]; e; e = next[e]) if (flow[e] > 0)
        {
            int y = to[e];
            if (p[y] > p[x] + cost[e])
            {
                p[y] = p[x] + cost[e];
            }
        }

        ll resFlow = 0, resCost = 0;
        while (1)
        {
            forn(i, N) d[i] = INF, used[i] = 0;
            d[ST] = 0;
            forn(_, N)
            {
                int x = -1;
                forn(i, N) if (!used[i] && (x == -1 || d[x] > d[i])) x = i;
                used[x] = 1;
                if (d[x] == INF) break;
                for (int e = head[x]; e; e = next[e]) if (flow[e] > 0)
                {
                    int y = to[e];
                    ll len = cost[e] + p[x] - p[y];
                    if (d[y] > d[x] + len)
                    {
                        d[y] = d[x] + len;
                        last[y] = e;
                    }
                }
            }
            
            if (d[EN] == INF) break;
            
            ll realCost = d[EN] + p[EN] - p[ST];
            if (flag && realCost > 0) break;

            int pushed = inf;
            int x = EN;
            while (x != ST)
            {
                int e = last[x];
                pushed = min(pushed, flow[e]);
                x = to[e ^ 1];
            }

            resCost += realCost * pushed;
            resFlow += pushed;

            x = EN;
            while (x != ST)
            {
                int e = last[x];
                flow[e] -= pushed;
                flow[e ^ 1] += pushed;
                x = to[e ^ 1];
            }

            forn(i, N) p[i] += d[i];
        }
        return mp(resFlow, resCost);
    }

    pair<ll, ll> maxFlow()
    {
        return _calc(0);
    }          

    pair<ll, ll> minCost()
    {
        return _calc(1);
    }          

    // HOW TO USE::
    // -- add adges using add(x, y, f, c), call setN(n)
    // -- run maxFlow/minCost, returns pair(flow, cost)
}
