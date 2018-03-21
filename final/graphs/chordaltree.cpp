void chordaltree(vector<vector<int>> e) {
    int n = e.size();

    vector<int> mark(n);
    set<pair<int, int> > st;
    for (int i = 0; i < n; i++) st.insert({-mark[i], i});

    vector<int> vct(n);
    vector<pair<int, int> > ted;
    vector<vector<int> > who(n);
    vector<vector<int> > verts(1);
    vector<int> cliq(n, -1);
    cliq.push_back(0);
    vector<int> last(n + 1, n);
    int prev = n + 1;
    for (int i = n - 1; i >= 0; i--) {
        int x = st.begin()->second;
        st.erase(st.begin());
        if (mark[x] <= prev) {
            vector<int> cur = who[x];
            cur.push_back(x);
            verts.push_back(cur);
            ted.push_back({cliq[last[x]], (int)verts.size() - 1});
        } else {
            verts.back().push_back(x);
        }
        for (int y : e[x]) {
            if (cliq[y] != -1) continue;
            who[y].push_back(x);
            st.erase({-mark[y], y});
            mark[y]++;
            st.insert({-mark[y], y});
            last[y] = x;
        }
        prev = mark[x];
        vct[i] = x;
        cliq[x] = (int)verts.size() - 1;
    }

    int k = verts.size();
    vector<int> pr(k);
    vector<vector<int> > g(k);
    for (auto o : ted) {
        pr[o.second] = o.first;
        g[o.first].push_back(o.second);
    }
}
