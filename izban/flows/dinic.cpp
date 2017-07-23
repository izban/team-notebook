#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


const int INF = (int)1.01e9;

struct Edge {
    int to, cap, flow;
};

struct Graph {
    int n;
    vector<vector<int> > e;
    vector<Edge> edges;
    vector<int> d, c;

    Graph() {}
    Graph(int _n) {
        n = _n;
        e.resize(n);
    }

    void addEdge(int from, int to, int cap) {
        e[from].push_back(edges.size());
        edges.push_back(Edge({to, cap, 0}));
        e[to].push_back(edges.size());
        edges.push_back(Edge({from, 0, 0}));
    }

    bool bfs() {
        d.assign(n, INF);
        c.assign(n, 0);
        vector<int> q(n);
        int qL = 0, qR = 0;
        d[0] = 0;
        q[qR++] = 0;
        while (qL < qR) {
            int v = q[qL++];
            for (int i = 0; i < (int)e[v].size(); i++) {
                Edge cur = edges[e[v][i]];
                if (d[cur.to] > d[v] + 1 && cur.flow < cur.cap) {
                    d[cur.to] = d[v] + 1;
                    q[qR++] = cur.to;
                }
            }
        } 
        return d[n - 1] != INF;
    }

    int dfs(int v, int flow) {
        if (v == n - 1) return flow;
        if (flow == 0) return 0;
        for (int &i = c[v]; i < (int)e[v].size(); i++) {
            Edge cur = edges[e[v][i]];
            if (d[cur.to] != d[v] + 1) continue;
            int pushed = dfs(cur.to, min(flow, cur.cap - cur.flow));
            if (pushed > 0) {
                edges[e[v][i]].flow += pushed;
                edges[e[v][i] ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll flow() {
        ll flow = 0;
        while (bfs()) {
            while (int pushed = dfs(0, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

   
    
#ifdef HOME
    cerr << "time: " << clock() / (double)CLOCKS_PER_SEC << endl;
#endif
    return 0;
}


