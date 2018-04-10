int getPart(pt v) {
    return ls(v.y, 0) || (eq(0, v.y) && ls(v.x, 0));
}

int cmpV(pt a, pt b) {
    int partA = getPart(a);
    int partB = getPart(b);
    if (partA < partB) return 1; 
    if (partA > partB) return -1;
    if (eq(0, a * b)) return 0;
    if (0 < a * b) return -1;
    return 1;
}

double planeInt(vector<Line> l) {
    sort(all(l), [](Line a, Line b) {
            int r = cmpV(a.v, b.v);
            if (r != 0) return r < 0;
            return a.O % a.v.rotate() > b.O % a.v.rotate();
        });
    
    l.resize(unique(all(l), [](Line A, Line B) { return cmpV(A.v, B.v) == 0; }) - l.begin());
    for (int i = 0; i < sz(l); i++)
        l[i].id = i;

    // if an infinite answer is possible
    int flagUp = 0;
    int flagDown = 0;
    for (int i = 0; i < sz(l); i++) {
        int part = getPart(l[i].v);
        if (part == 1) flagUp = 1;
        if (part == 0) flagDown = 1;
    }
    if (!flagUp || !flagDown) return -1;

    for (int i = 0; i < sz(l); i++) {
        pt v = l[i].v;
        pt u = l[(i + 1) % sz(l)].v;
        if (eq(0, v * u) && ls(v % u, 0)) {
            pt dir = l[i].v.rotate();
            if (le(l[(i + 1) % sz(l)].O % dir, l[i].O % dir)) return 0;
            return -1;
        }
        if (ls(v * u, 0))
            return -1;
    }  
    // main part
    vector<Line> st;
    for (int tt = 0; tt < 2; tt++) {
        for (auto L: l) {
            for (; sz(st) >= 2 && le(st[sz(st) - 2].v * (st.back() * L - st[sz(st) - 2].O), 0); st.pop_back());
            st.pb(L);
            if (sz(st) >= 2 && le(st[sz(st) - 2].v * st.back().v, 0)) return 0; // useless line
        }
    }
    vector<int> use(sz(l), -1); 
    int left = -1, right = -1;
    for (int i = 0; i < sz(st); i++) {
        if (use[st[i].id] == -1) {
            use[st[i].id] = i;
        }
        else {
            left = use[st[i].id];
            right = i;
            break;
        }
    }
    vector<Line> tmp;
    for (int i = left; i < right; i++)
        tmp.pb(st[i]);
    vector<pt> res;
    for (int i = 0; i < (int)tmp.size(); i++) 
        res.pb(tmp[i] * tmp[(i + 1) % tmp.size()]);
    double area = 0;
    for (int i = 0; i < (int)res.size(); i++)
        area += res[i] * res[(i + 1) % res.size()];
    return area / 2;
}
