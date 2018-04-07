namespace mimimi /* ^_^ */ {
    const int N = 100555;
    const int S = 3;
    int e[N][S];
    int label[N];
    vector<int> eb[N][S];
    int ans[N];
    void solve(int n) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < S; ++j)
                eb[i][j].clear();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < S; ++j)
                eb[e[i][j]][j].push_back(i);
        vector<unordered_set<int>> classes(*max_element(label, label + n) + 1);
        for (int i = 0; i < n; ++i)
            classes[label[i]].insert(i);
        for (int i = 0; i < sz(classes); ++i)
            if (classes[i].empty()) {
                classes[i].swap(classes.back());
                classes.pop_back();
                --i;
            }
        for (int i = 0; i < sz(classes); ++i)
            for (int v : classes[i])
                ans[v] = i;
        for (int i = 0; i < sz(classes); ++i)
            for (int c = 0; c < S; ++c) {
                unordered_map<int, unordered_set<int>> involved;
                for (int v : classes[i])
                    for (int nv : eb[v][c])
                        involved[ans[nv]].insert(nv);
                for (auto &pp : involved) {
                    int cl = pp.X;
                    auto &cls = classes[cl];
                    if (sz(pp.Y) == sz(cls))
                        continue;
                    for (int x : pp.Y)
                        cls.erase(x);
                    if (sz(cls) < sz(pp.Y))
                        cls.swap(pp.Y);
                    for (int x : pp.Y)
                        ans[x] = sz(classes);
                    classes.push_back(move(pp.Y));
                }
            }
    }
    /* Usage: initialize edges: e[vertex][character]
                         labels: label[vertex]
              solve(n)
              ans[] - classes
    */
}
