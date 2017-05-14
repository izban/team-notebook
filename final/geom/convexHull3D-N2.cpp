
struct Plane {
    pt O, v;
    vector<int> id;
};

vector<Plane> convexHull3(vector<pt> p) {
    vector<Plane> res;
    int n = p.size();
    for (int i = 0; i < n; i++)
        p[i].id = i;
    for (int i = 0; i < 4; i++) {
        vector<pt> tmp;
        for (int j = 0; j < 4; j++)
            if (i != j)
                tmp.pb(p[j]);
        res.pb({tmp[0], (tmp[1] - tmp[0]) * (tmp[2] - tmp[0]), {tmp[0].id, tmp[1].id, tmp[2].id}});
        if ((p[i] - res.back().O) % res.back().v > 0) {
            res.back().v = res.back().v * -1;
            swap(res.back().id[0], res.back().id[1]);
        }
    }
    vector<vector<int>> use(n, vector<int>(n, 0));
    int tmr = 0;
    for (int i = 4; i < n; i++) {
        int cur = 0;
        tmr++;
        vector<pair<int,int>> curEdge;
        for (int j = 0; j < sz(res); j++) {
            if ((p[i] - res[j].O) % res[j].v > 0) {
                for (int t = 0; t < 3; t++) {
                    int v = res[j].id[t]; 
                    int u = res[j].id[(t + 1) % 3]; 
                    use[v][u] = tmr;
                    curEdge.pb({v, u});
                } 
            }
            else {
                res[cur++] = res[j];
            }
        }
        res.resize(cur);
        for (auto x: curEdge) {
            if (use[x.S][x.F] == tmr) continue;
            res.pb({p[i], (p[x.F] - p[i]) * (p[x.S] - p[i]), {x.F, x.S, i}});
        }
    }
    return res;
}

// plane in 3d
//(A, v) * (B, u) -> (O, n)

pt n = v * u;
pt m = v * n;
double t = (B - A) % u / (u % m);
pt O = A - m * t;
