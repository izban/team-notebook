namespace domtree {
    const int MAXN = 300100;
    int n;
    vector<int> e[MAXN];
    vector<int> g[MAXN];
    int par[MAXN];
    int in[MAXN], rin[MAXN], tmr;
    int dom[MAXN], sdom[MAXN], cmn[MAXN];
    int p[MAXN];
    int adom[MAXN];
    vector<int> vct[MAXN];

    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            e[i].clear();
        }
    }

    void addEdge(int from, int to) {
        e[from].push_back(to);
    }

    void dfs(int v) {
        in[v] = tmr++; 
        rin[in[v]] = v;
        for (int to : e[v]) {
            if (in[to] == -1) {
                dfs(to);
                par[in[to]] = in[v];
            }
            g[in[to]].push_back(in[v]);
        }
    }

    int get(int u, int x = 0) {
        if (u == p[u]) return x ? -1 : u;
        int v = get(p[u], x + 1);
        if (v < 0) return u;
        if (sdom[cmn[p[u]]] < sdom[cmn[u]]) cmn[u] = cmn[p[u]];
        p[u] = v;
        return x ? v : cmn[u]; 
    }

    void uni(int u, int v) {
        p[v] = u;
    }

    void calc() {
        for (int i = 0; i < n; i++) {
            in[i] = -1;
            adom[i] = -1;
            dom[i] = sdom[i] = p[i] = cmn[i] = i;
            vct[i].clear();
            g[i].clear();
        }
        tmr = 0;
        dfs(0);
        for (int i = tmr - 1; i >= 0; i--) {
            for (int to : g[i]) sdom[i] = min(sdom[i], sdom[get(to)]);
            if (i > 0) vct[sdom[i]].push_back(i);
            for (int w : vct[i]) {
                int v = get(w);
                if (sdom[v] == sdom[w]) dom[w] = sdom[w];
                else dom[w] = v;
            }
            if (i > 0) uni(par[i], i);
        }
        for (int i = 1; i < tmr; i++) {
            if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
            adom[rin[i]] = rin[dom[i]];
        }
    }
}
