#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9;
struct Edge {
    int from, to, w, id;
};
namespace dmst {
    vector<int> solve(int n, vector<Edge> &edges) {
        if (n == 1) return vector<int>();
        int m = edges.size();
        vector<vector<int> > e(n);
        for (int i = 0; i < m; i++) {
            if (edges[i].from != edges[i].to) e[edges[i].to].push_back(i); 
        }
        vector<int> nxtEdge(n, -1);
        for (int i = 1; i < n; i++) {
            int mn = INF;
            for (int id : e[i]) mn = min(mn, edges[id].w);
            for (int id : e[i]) {
                edges[id].w -= mn;
                if (edges[id].w == 0) nxtEdge[i] = id;
            }
        }
        vector<int> p(n);
        for (int i = 0; i < n; i++) p[i] = i;
        vector<char> used(n);
        used[0] = 1;
        int cur = 1;
        vector<int> vct;
        while (!used[cur]) {
            used[cur] = 1;
            vct.push_back(cur);
            cur = edges[nxtEdge[cur]].from;
        }
        vector<int> ans;
        while (!vct.empty()) {
            ans.push_back(nxtEdge[vct.back()]);
            if (vct.back() == cur) break;
            p[vct.back()] = cur;
            vct.pop_back();
        }
        int nn = 0;
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            if (p[i] == i) c[i] = nn++;
        }
        for (int i = 0; i < m; i++) {
            edges[i].from = c[p[edges[i].from]];
            edges[i].to = c[p[edges[i].to]];
        }
        auto nans = solve(nn, edges);
        for (auto id : ans) nans.push_back(id);
        return nans;
    }

    // root is 0
    vector<int> getMst(int n, vector<Edge> edges) {
        auto cedges = edges;
        auto res = solve(n, cedges);
        vector<char> used(n);
        vector<int> ans;
        for (int id : res) {
            if (!used[edges[id].to]) {
                used[edges[id].to] = 1;
                ans.push_back(id);
            }
        }
        return ans;
    }
}

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    /*{
        int n = 500;
        int m = 10000;
        vector<Edge> e;
        for (int i = 1; i < n; i++) e.push_back(Edge({i - 1, i, rand() % (int)1e6 + 1, (int)e.size()}));
        while ((int)e.size() < m) {
            int u = rand() % n;
            int v = rand() % n;
            if (u != v) e.push_back(Edge({u, v, rand() % (int)1e6 + 1, (int)e.size()}));
        }
        cout << dmst::getMst(n, e).size() << endl;
        return 0;
    }*/

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
        for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] + 1 << " \n"[i + 1 == (int)ans.size()];
    }

    return 0;
}

