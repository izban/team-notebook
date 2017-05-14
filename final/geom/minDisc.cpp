
pair<pt, dbl> minDisc(vector<pt> p) {
    int n = p.size();
    pt O = pt(0, 0);
    dbl R = 0;
    random_shuffle(all(p));
    for (int i = 0; i < n; i++) {
        if (ls(R, (O - p[i]).len())) {
            O = p[i];
            R = 0;
            for (int j = 0; j < i; j++) {
                if (ls(R, (O - p[j]).len())) {
                    O = (p[i] + p[j]) / 2;    
                    R = (p[i] - p[j]).len() / 2;
                    for (int k = 0; k < j; k++) {
                        if (ls(R, (O - p[k]).len())) {
                            Line l1((p[i] + p[j]) / 2, (p[i] + p[j]) / 2 + (p[i] - p[j]).rotate()); 
                            Line l2((p[k] + p[j]) / 2, (p[k] + p[j]) / 2 + (p[k] - p[j]).rotate()); 
                            O = l1 * l2;
                            R = (p[i] - O).len();
                        }
                    }
                }
            }
        }
    }
    return {O, R};
}



