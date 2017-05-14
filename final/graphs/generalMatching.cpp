//COPYPASTED FROM E-MAXX
namespace GeneralMatching {
    const int MAXN = 256;
    int n;
    vector<int> g[MAXN];
    int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
    bool used[MAXN], blossom[MAXN];
     
    int lca (int a, int b) {
	    bool used[MAXN] = { 0 };
	    for (;;) {
		    a = base[a];
		    used[a] = true;
		    if (match[a] == -1)  break;
		    a = p[match[a]];
	    }
	    for (;;) {
		    b = base[b];
		    if (used[b])  return b;
		    b = p[match[b]];
	    }
    }
    
    void mark_path (int v, int b, int children) {
	    while (base[v] != b) {
		    blossom[base[v]] = blossom[base[match[v]]] = true;
		    p[v] = children;
		    children = match[v];
		    v = p[match[v]];
	    }
    }
     
    int find_path (int root) {
	    memset (used, 0, sizeof used);
	    memset (p, -1, sizeof p);
	    for (int i=0; i<n; ++i)
		    base[i] = i;
     
	    used[root] = true;
	    int qh=0, qt=0;
	    q[qt++] = root;
	    while (qh < qt) {
		    int v = q[qh++];
		    for (size_t i=0; i<g[v].size(); ++i) {
			    int to = g[v][i];
			    if (base[v] == base[to] || match[v] == to)  continue;
			    if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
				    int curbase = lca (v, to);
				    memset (blossom, 0, sizeof blossom);
				    mark_path (v, curbase, to);
				    mark_path (to, curbase, v);
				    for (int i=0; i<n; ++i)
					    if (blossom[base[i]]) {
						    base[i] = curbase;
						    if (!used[i]) {
							    used[i] = true;
							    q[qt++] = i;
						    }
					    }
			    }
			    else if (p[to] == -1) {
				    p[to] = v;
				    if (match[to] == -1)
					    return to;
				    to = match[to];
				    used[to] = true;
				    q[qt++] = to;
			    }
		    }
	    }
	    return -1;
    }
    
    vector<pair<int, int> > solve(int _n, vector<pair<int, int> > edges) {
        n = _n;
        for (int i = 0; i < n; i++) g[i].clear();
        for (auto o : edges) {
            g[o.first].push_back(o.second);
            g[o.second].push_back(o.first);
        }
        memset (match, -1, sizeof match);
	    for (int i=0; i<n; ++i) {
		    if (match[i] == -1) {
			    int v = find_path (i);
			    while (v != -1) {
				    int pv = p[v],  ppv = match[pv];
				    match[v] = pv,  match[pv] = v;
				    v = ppv;
			    }
		    }
	    }
	    vector<pair<int, int> > ans;
	    for (int i = 0; i < n; i++) {
            if (match[i] > i) {
                ans.push_back(make_pair(i, match[i]));
            }
        }
        return ans;
    }
}
