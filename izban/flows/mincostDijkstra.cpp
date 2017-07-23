#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


const int INF = (int)1.01e9;

struct Edge {
    int to, cap, flow, cost;
};

struct Graph {
    int n;
    vector<vector<int> > e;
    vector<Edge> edges;
    vector<int> d, fl, pr, p;

    Graph() {}
    Graph(int _n) {
        n = _n;
        e.resize(n);
    }

    void addEdge(int from, int to, int cap, int cost) {
        e[from].push_back(edges.size());
        edges.push_back(Edge({to, cap, 0, cost}));
        e[to].push_back(edges.size());
        edges.push_back(Edge({from, 0, 0, -cost}));
    }

    bool dijkstra() {
        d.assign(n, INF);
        fl.assign(n, 0);
        pr.resize(n);

        priority_queue<pair<int, int> > q;
        d[0] = 0;
        fl[0] = INF;
        q.push(make_pair(-d[0], 0));
        while (!q.empty()) {
            auto o = q.top();
            q.pop();
            if (d[o.second] != -o.first) continue;
            int v = o.second;

            for (int i = 0; i < (int)e[v].size(); i++) {
                Edge cur = edges[e[v][i]];
                if (d[cur.to] > d[v] + cur.cost + p[v] - p[cur.to] && cur.flow < cur.cap) {
                    d[cur.to] = d[v] + cur.cost + p[v] - p[cur.to];
                    fl[cur.to] = min(fl[v], cur.cap - cur.flow);
                    pr[cur.to] = e[v][i];
                    q.push(make_pair(-d[cur.to], cur.to));
                }
            }
        }
        for (int i = 0; i < n; i++) p[i] += d[i];
        return fl[n - 1] != 0;
    }

    pair<int, int> mincost() {
        pair<int, int> ans = {0, 0};
        p.assign(n, 0);
        while (1) {
            if (!dijkstra()) break;
            ans.first += fl[n - 1];
            ans.second += p[n - 1];
            int v = n - 1;
            while (v != 0) {
                edges[pr[v]].flow += fl[n - 1];
                edges[pr[v] ^ 1].flow -= fl[n - 1];
                v = edges[pr[v] ^ 1].to;
            } 
        }
        return ans;
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




