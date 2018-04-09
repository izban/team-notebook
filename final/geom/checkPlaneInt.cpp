
bool checkPoint(vector<Line> l, pt& ret) {
    random_shuffle(all(l)); 
    pt A = l[0].O;
    for (int i = 1; i < sz(l); i++) {
        if (!le(0, l[i].v * (A - l[i].O))) {
            dbl mn = -INF;    
            dbl mx = INF;
            for (int j = 0; j < i; j++) {
                if (eq(l[j].v * l[i].v, 0)) {
                    if (l[j].v % l[i].v < 0 && (l[j].O - l[i].O) % l[i].v.rotate() <= 0) {
                        return false;
                    }
                }
                else {
                    pt u = l[j].v.rotate();
                    dbl proj = (l[j].O - l[i].O) % u / (l[i].v % u);
                    if (l[i].v * l[j].v > 0) {
                        mx = min(mx, proj);
                    }
                    else {
                        mn = max(mn, proj);
                    }
                }
            }
            if (mn <= mx) {
                A = l[i].O + l[i].v * mn;
            }
            else {
                return false;
            }
        }
    }
    ret = A;
    return true;
}

