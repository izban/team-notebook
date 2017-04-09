int getPart(pt v) {
    return less(0, v.y) || (equal(0, v.y) && less(v.x, 0));
}

int cmpV(pt a, pt b) {
    int partA = getPart(a);
    int partB = getPart(b);
    if (partA < partB) return -1; 
    if (partA > partB) return 1;
    if (equal(0, a * b)) return 0;
    if (0 < a * b) return -1;
    return 1;
}

double planeInt(vector<Line> l) {
    int n = l.size();
    sort(all(l), [](Line a, Line b) {
            int r = cmpV(a.v, b.v);
            if (r != 0) return r < 0;
            return a.O % a.v.rotate() < b.O % a.v.rotate();
        });
    
    int cur = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        for (; i < n && cmpV(l[j].v, l[i].v) == 0 && cmpV(l[i].v, l[j].v) == 0; i++);
        l[cur++] = l[i - 1];
    }
    n = cur;

    for (int i = 0; i < n; i++)
        l[i].id = i;

    int flagUp = 0;
    int flagDown = 0;
    for (int i = 0; i < n; i++) {
        int part = getPart(l[i].v);
        if (part == 1) flagUp = 1;
        if (part == 0) flagDown = 1;
    }
    if (!flagUp || !flagDown) return -1;

    for (int i = 0; i < n; i++) {
        pt v = l[i].v;
        pt u = l[(i + 1) % n].v;
        if (equal(0, v * u) && less(v % u, 0)) {
            pt dir = l[i].v.rotate();
            if (lessE(l[(i + 1) % n].O % dir, l[i].O % dir)) return 0;
            return -1;
        }
        if (less(v * u, 0))
            return -1;
    }  
    
    cur = 0;
    vector<Line> st(n * 2);
    for (int tt = 0; tt < 2; tt++) {
        for (int i = 0; i < n; i++) {
            for (; cur >= 2; cur--) {
                pt G = st[cur - 1] * l[i];
                if (!lessE(st[cur - 2].v * (G - st[cur - 2].O), 0))
                    break;
            }
            st[cur++] = l[i];
            if (cur >= 2 && lessE(st[cur - 2].v * st[cur - 1].v, 0)) return 0;
        }
    }
    vector < int > use(n, -1); 
    int left = -1, right = -1;
    for (int i = 0; i < cur; i++) {
        if (use[st[i].id] == -1) {
            use[st[i].id] = i;
        }
        else {
            left = use[st[i].id];
            right = i;
            break;
        }
    }
    vector < Line > tmp;
    for (int i = left; i < right; i++)
        tmp.pb(st[i]);
    vector < pt > res;
    for (int i = 0; i < (int)tmp.size(); i++) 
        res.pb(tmp[i] * tmp[(i + 1) % tmp.size()]);
    double area = 0;
    for (int i = 0; i < (int)res.size(); i++)
        area += res[i] * res[(i + 1) % res.size()];
    return area / 2;
}
