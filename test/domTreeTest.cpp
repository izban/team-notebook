#include <bits/stdc++.h>
using namespace std;

// lesnoe ozero 2017, some task
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

const int MAXN = 100100;
int n, m;
vector<int> e[MAXN], g[MAXN];
int vis[MAXN];
int c[MAXN], cc;
vector<int> vct;

void dfs1(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    for (int to : e[v]) dfs1(to);
    vct.push_back(v);
}

void dfs2(int v) {
    if (c[v] != -1) return;
    c[v] = cc;
    for (int to : g[v]) dfs2(to); 
}

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++) {
            e[i].clear();
            g[i].clear();
        }

        vector<pair<int, int> > ed(m);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &ed[i].first, &ed[i].second);
            ed[i].first--;
            ed[i].second--;
        }

        for (int i = 0; i < m; i++) {
            e[ed[i].first].push_back(ed[i].second);
            g[ed[i].second].push_back(ed[i].first);
        }
        vct.clear();
        for (int i = 0; i < n; i++) vis[i] = 0;
        for (int i = 0; i < n; i++) dfs1(i);

        for (int i = 0; i < n; i++) c[i] = -1;
        cc = 0;
        for (int i = 0; i < n; i++) {
            int v = vct[n - i - 1];
            if (c[v] != -1) continue;
            dfs2(v);
            cc++;    
        }

        vector<int> ans(m, 0);
        for (int it = 0; it < 2; it++) {
            domtree::init(n + m + 1);
            for (int i = 0; i < m; i++) if (c[ed[i].first] == c[ed[i].second]) {
                domtree::addEdge(1 + ed[i].first, 1 + n + i);
                domtree::addEdge(1 + n + i, 1 + ed[i].second);
            }
            vector<char> was(cc);
            for (int i = 0; i < n; i++) {
                if (!was[c[i]]) {
                    was[c[i]] = 1;
                    domtree::addEdge(0, 1 + i);
                } 
            }
            domtree::calc();
            for (int i = 1; i < domtree::n; i++) {
                if (domtree::adom[i] >= 1 + n) {
                    ans[domtree::adom[i] - 1 - n] = 1;
                }
            }

            for (int i = 0; i < m; i++) swap(ed[i].first, ed[i].second);
        }
        for (int i = 0; i < m; i++) printf("%d", ans[i]);
        printf("\n");
    } 

    return 0;
}
