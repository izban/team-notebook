ll furthestPoints(vector<pt> p) {
    int n = p.size();
    int cur = 1;
    ll answer = 0;
    for (int i = 0; i < n; i++) {
        for (; (p[(i + 1) % n] - p[i]) * (p[(cur + 1) % n] - p[cur]) > 0; cur = (cur + 1) % n);
        answer = max(answer, (p[i] - p[cur]).len2());
    }
    return answer;
}
