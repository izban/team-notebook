#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9;
struct Edge {
    int from, to, w, id;
};
namespace dmst {
    int n;
    vector<int> p;
    vector<Edge> edges;

    int get(int x) {
        if (x == p[x]) return x;
        return p[x] = get(p[x]);
    }

    void uni(int u, int v) {
        p[get(v)] = get(u);
    }

    vector<Edge> solve() {
        vector<int> id(n, -1);
        vector<int> vert;
        int cn = 0;
        for (int i = 0; i < n; i++) if (get(i) == i) {
            vert.push_back(i);
            id[i] = cn++;
        }
        if (cn == 1) return vector<Edge>();

        vector<vector<int> > e(cn);
        for (int i = 0; i < (int)edges.size(); i++) {
            if (get(edges[i].to) != get(edges[i].from)) {
                e[id[get(edges[i].to)]].push_back(i);  
            }
        }
        
        vector<int> nxtId(cn, -1);
        for (int i = 0; i < cn; i++) {
            int mn = INF;
            for (int id : e[i]) mn = min(mn, edges[id].w);
            for (int id : e[i]) {
                edges[id].w -= mn;
                if (edges[id].w == 0) nxtId[i] = id;
            }
        }

        vector<char> vis(cn);
        vis[0] = 1;
        int cur = 1; 
        while (!vis[cur]) {
            vis[cur] = 1;
            cur = id[get(edges[nxtId[cur]].from)];
        }
        vector<Edge> ans;
        if (cur == 0) {
            for (int i = 0; i < cn; i++) {
                if (vis[i] && i != 0) {
                    ans.push_back(edges[nxtId[i]]);
                    uni(0, vert[i]); 
                }
            }
            auto nans = solve();
            for (auto ee : nans) ans.push_back(ee);
            return ans;
        }
        vector<int> cp = p;
        int o = cur;
        while (1) {
            uni(vert[o], vert[cur]); 
            ans.push_back(edges[nxtId[cur]]);
            int to = id[get(edges[nxtId[cur]].from)];
            if (to == o) break;
            cur = to;
        }
        vector<Edge> nedges = solve();
        p = cp;
        vector<char> covered(cn);
        for (auto ee : nedges) covered[id[get(ee.to)]] = 1;
        for (auto ee : ans) if (!covered[id[get(ee.to)]]) nedges.push_back(ee); 
        return nedges;
    }

    // root is 0
    vector<Edge> getMst(int _n, vector<Edge> _edges) {    
        n = _n;
        edges = _edges;
        p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
        
        return solve();
    }
}

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            Edge e;
            scanf("%d%d%d", &e.from, &e.to, &e.w);
            e.from--; e.to--;
            e.id = i;
            edges.push_back(e);
        }
        auto ans = dmst::getMst(n, edges);
        cout << ans.size() << endl;
        for (int i = 0; i < (int)ans.size(); i++) cout << ans[i].id + 1 << " \n"[i + 1 == (int)ans.size()];
    }

    return 0;
}
