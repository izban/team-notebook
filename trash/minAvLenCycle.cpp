// opentrains 10072: I
// team : SPb ITMO University 1
#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define pw(x) (1LL<<(x))
#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")" << endl
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z <<  ") = (" << x << ", " << y << ", " << z << ")" << endl

using namespace std;

typedef long long ll;
typedef double dbl;
typedef vector<int> vi;
typedef pair<int, int> pi;

const int INF = 1.01e9;
const dbl EPS = 1e-9;

/* --- main part --- */

struct Edge {
	int from, to, cap, flow;
	double cost;

};

struct Graph {
	int n;
	vector<Edge> edges;
	vector<vector<int> > e;

	Graph(int _n) {
		n = _n;
		e.resize(n);
	}

	void addEdge(int from, int to, int cap, double cost) {
		e[from].push_back(edges.size());
		edges.push_back({ from, to, cap, 0, cost });
		e[to].push_back(edges.size());
		edges.push_back({ to, from, 0, 0, -cost });
	}

	void maxflow() {
		while (1) {
			queue<int> q;
			vector<int> d(n, INF);
			vector<int> pr(n, -1);
			q.push(0);
			d[0] = 0;
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				for (int i = 0; i < (int)e[v].size(); i++) {
					Edge cur = edges[e[v][i]];
					if (d[cur.to] > d[v] + 1 && cur.flow < cur.cap) {
						d[cur.to] = d[v] + 1;
						pr[cur.to] = e[v][i];
						q.push(cur.to);
					}
				}
			}
			if (d[n - 1] == INF) break;
			int v = n - 1;
			while (v) {
				edges[pr[v]].flow++;
				edges[pr[v] ^ 1].flow--;
				v = edges[pr[v]].from;
			}
		}
	}

	bool findcycle() {
		int iters = n;
		vector<int> changed;
		for (int i = 0; i < n; i++) changed.push_back(i);

		vector<vector<double> > d(iters + 1, vector<double>(n, INF));
		vector<vector<int> > p(iters + 1, vector<int>(n, -1));
		d[0].assign(n, 0);
		for (int it = 0; it < iters; it++) {
			d[it + 1] = d[it];
			vector<int> nchanged(n, 0);
			for (int v : changed) {
				for (int id : e[v]) {
					Edge cur = edges[id];
					if (d[it + 1][cur.to] > d[it][v] + cur.cost && cur.flow < cur.cap) {
						d[it + 1][cur.to] = d[it][v] + cur.cost;
						p[it + 1][cur.to] = id;
						nchanged[cur.to] = 1;
					}
				}
			}
			changed.clear();
			for (int i = 0; i < n; i++) if (nchanged[i]) changed.push_back(i);
		}
		if (changed.empty()) return 0;

		int bestU = 0, bestK = 1;
		double bestAns = INF;
		for (int u = 0; u < n; u++) {
			double curMax = -INF;
			for (int k = 0; k < iters; k++) {
				double curVal = (d[iters][u] - d[k][u]) / (iters - k);
				curMax = max(curMax, curVal);
			}
			if (bestAns > curMax) {
				bestAns = curMax;
				bestU = u;
			}
		}

		int v = bestU;
		int it = iters;
		vector<int> was(n, -1);
		while (was[v] == -1) {
			was[v] = it;
			v = edges[p[it][v]].from;
			it--;
		}
		int vv = v;
		it = was[v];
		double sum = 0;
		do {
			edges[p[it][v]].flow++;
			sum += edges[p[it][v]].cost;
			edges[p[it][v] ^ 1].flow--;
			v = edges[p[it][v]].from;
			it--;
		} while (v != vv);
		return 1;
	}
};



#define TASK "inhabitants"
int main() {
	assert(freopen(TASK".in", "r", stdin));
#ifndef HOME
	assert(freopen(TASK".out", "w", stdout));
#endif

	int n, m;
	while (cin >> n >> m) {
		Graph gr(n);
		for (int i = 0; i < m; i++) {
			int fr, to, cap, cost;
			cin >> fr >> to >> cap >> cost;
			--fr; --to;
			gr.addEdge(fr, to, cap, cost);
		}

		gr.maxflow();

		double l = -15, r = 15;
		for (int it = 0; it < 50; it++) {
			double x = (l + r) / 2.0;

			Graph g = gr;
			for (int i = 0; i < m; i++) {
				g.edges[i * 2].cost -= x;
				g.edges[i * 2 + 1].cost += x;
			}

			while (g.findcycle());

			double sum = 0;
			for (int i = 0; i < m * 2; i++) {
				sum += max(g.edges[i].flow, 0) * g.edges[i].cost;
			}

			if (sum < 0) r = x;
			else l = x;
		}
		printf("%.15f\n", r);
	}


#ifdef HOME
	eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
#endif
	return 0;
}


