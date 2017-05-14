
struct Meta { 
    int type; // 0 - seg, 1 - circle
    pt O;
    dbl R;
};

const Meta SEG = {0, pt(0, 0), 0};

vector<pair<pt, Meta>> cut(vector<pair<pt, Meta>> p, Line l) {
    vector<pair<pt,Meta>> res;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        pt A = p[i].F;
        pt B = p[(i + 1) % n].F;
        if (le(0, l.v * (A - l.O))) {
            if (eq(0, l.v * (A - l.O)) && p[i].S.type == 1 && ls(0, l.v % (p[i].S.O - A)))
                res.pb({A, SEG});
            else
                res.pb(p[i]);
        }
        if (p[i].S.type == 0) {
            if (sign(l.v * (A - l.O)) * sign(l.v * (B - l.O)) == -1) {
                pt FF = Line(A, B) * l;
                res.pb(make_pair(FF, SEG));
            }
        }
        else {
            pt E, F;  
            if (intCL(p[i].S.O, p[i].S.R, l, E, F)) {          
                if (onArc(p[i].S.O, A, E, B))
                    res.pb({E, SEG});
                if (onArc(p[i].S.O, A, F, B))
                    res.pb({F, p[i].S});
            } 
        }
    }
    return res;
}
