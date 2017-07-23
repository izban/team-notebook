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
    vector<int> d, fl, q, inq, pr;

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

    bool bfs() {
        d.assign(n, INF);
        q.resize(n + 1);
        fl.assign(n, 0);
        pr.resize(n);
        inq.assign(n, 0);

        int qL = 0, qR = 0;
        q[qR++] = 0;
        d[0] = 0;
        fl[0] = INF;
        inq[0] = 1;
        while (qL != qR) {
            int v = q[qL];
            qL = (qL + 1) % (n + 1);
            inq[v] = 0;

            for (int i = 0; i < (int)e[v].size(); i++) {
                Edge cur = edges[e[v][i]];
                if (d[cur.to] > d[v] + cur.cost && cur.flow < cur.cap) {
                    d[cur.to] = d[v] + cur.cost;
                    fl[cur.to] = min(fl[v], cur.cap - cur.flow);
                    pr[cur.to] = e[v][i];
                    if (!inq[cur.to]) {
                        inq[cur.to] = 1;
                        q[qR] = cur.to;
                        qR = (qR + 1) % (n + 1);
                    }
                }
            }
        }
        return fl[n - 1] != 0;
    }

    pair<int, int> mincost() {
        pair<int, int> ans = {0, 0};
        while (1) {
            if (!bfs()) break;
            ans.first += fl[n - 1];
            ans.second += d[n - 1];
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



