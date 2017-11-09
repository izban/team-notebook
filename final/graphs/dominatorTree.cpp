namespace domtree {
    const int K = 18;
    const int N = 1 << K;

    int n, root;
    vector<int> e[N], g[N];
    int sdom[N], dom[N];
    int p[N][K], h[N], pr[N];
    int in[N], out[N], tmr, rev[N];

    void init(int _n, int _root) {
        n = _n;
        root = _root;
        tmr = 0;
        for (int i = 0; i < n; i++) {
            e[i].clear();
            g[i].clear();
            in[i] = -1;
        }
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int v) {
        in[v] = tmr++; 
        for (int to : e[v]) {
            if (in[to] != -1) continue;
            pr[to] = v;
            dfs(to);
        }
        out[v] = tmr - 1;
    }

    int lca(int u, int v) {
        if (h[u] < h[v]) swap(u, v);
        for (int i = 0; i < K; i++) if ((h[u] - h[v]) & (1 << i)) u = p[u][i];
        if (u == v) return u;
        for (int i = K - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }

    void solve(int _n, int _root, vector<pair<int, int> > _edges) {
        init(_n, _root);
        for (auto ed : _edges) addEdge(ed.first, ed.second);

        dfs(root); 
        for (int i = 0; i < n; i++) if (in[i] != -1) rev[in[i]] = i;
        segtree tr(tmr); // a[i]:=min(a[i],x) and return a[i]
        for (int i = tmr - 1; i >= 0; i--) {
            int v = rev[i];
            int cur = i;
            for (int to : g[v]) {
                if (in[to] == -1) continue;
                if (in[to] < in[v]) cur = min(cur, in[to]);
                else cur = min(cur, tr.get(in[to]));
            } 
            sdom[v] = rev[cur];
            tr.upd(in[v], out[v], in[sdom[v]]);
        }
        for (int i = 0; i < tmr; i++) {
            int v = rev[i];
            if (i == 0) {
                dom[v] = v;
                h[v] = 0;
            } else {
                dom[v] = lca(sdom[v], pr[v]);
                h[v] = h[dom[v]] + 1;
            }
            p[v][0] = dom[v];
            for (int j = 1; j < K; j++) p[v][j] = p[p[v][j - 1]][j - 1];
        }
        for (int i = 0; i < n; i++) if (in[i] == -1) dom[i] = -1;
    }
}
