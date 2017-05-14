namespace hld {
    const int N = 1 << 17;
    int par[N], heavy[N], h[N];
    int root[N], pos[N];
    int n;
    vector<vector<int> > e;
    segtree tree;

    int dfs(int v) {
        int sz = 1, mx = 0;
        for (int to : e[v]) {
            if (to == par[v]) continue;
            par[to] = v; 
            h[to] = h[v] + 1;
            int cur = dfs(to);
            if (cur > mx) heavy[v] = to, mx = cur;
            sz += cur;
        }
        return sz;
    }

    template <typename T>
    void path(int u, int v, T op) {
        for (; root[u] != root[v]; v = par[root[v]]) {
            if (h[root[u]] > h[root[v]]) swap(u, v);
            op(pos[root[v]], pos[v] + 1);
        }
        if (h[u] > h[v]) swap(u, v);
        op(pos[u], pos[v] + 1);
    }

    void init(vector<vector<int> > _e) {
        e = _e;
        n = e.size();
        tree = segtree(n);
        memset(heavy, -1, sizeof(heavy[0]) * n);
        par[0] = -1;
        h[0] = 0;
        dfs(0);
        for (int i = 0, cpos = 0; i < n; i++) {
            if (par[i] == -1 || heavy[par[i]] != i) {
                for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    pos[j] = cpos++;
                }
            }
        }
    }

    void add(int v, int x) {
        tree.add(pos[v], x);
    }

    int get(int u, int v) {
        int res = 0;
        path(u, v, [&](int l, int r) {
            res = max(res, tree.get(l, r));
        });
        return res;
    }
}
