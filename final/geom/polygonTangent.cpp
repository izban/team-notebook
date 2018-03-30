pt tangent(vector<pt>& p, pt O, int cof) {
    int step = 1;
    for (; step < (int)p.size(); step *= 2);
    int pos = 0;
    int n = p.size();
    for (; step > 0; step /= 2) {
        int best = pos;
        for (int dx = -1; dx <= 1; dx += 2) {
            int id = ((pos + step * dx) % n + n) % n;
            if ((p[id] - O) * (p[best] - O) * cof > 0)
                best = id;
        }
        pos = best;
    }
    return p[pos];
}
