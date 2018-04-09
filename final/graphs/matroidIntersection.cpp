    // check(ctaken, 1) -- first matroid
    // check(ctaken, 2) -- second matroid    
    vector<char> taken(m);
    while (1) {
        vector<vector<int>> e(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (taken[i] && !taken[j]) {
                    auto ctaken = taken;
                    ctaken[i] = 0;
                    ctaken[j] = 1;
                    if (check(ctaken, 2)) {
                        e[i].push_back(j);
                    }
                }
                if (!taken[i] && taken[j]) {
                    auto ctaken = taken;
                    ctaken[i] = 1;
                    ctaken[j] = 0;
                    if (check(ctaken, 1)) {
                        e[i].push_back(j);
                    }
                }
            }
        }
        vector<int> type(m);
        // 0 -- cant, 1 -- can in \2, 2 -- can in \1
        for (int i = 0; i < m; i++) {
            if (!taken[i]) {
                auto ctaken = taken;
                ctaken[i] = 1;
                if (check(ctaken, 2)) type[i] |= 1;
            }
            if (!taken[i]) {
                auto ctaken = taken;
                ctaken[i] = 1;
                if (check(ctaken, 1)) type[i] |= 2;
            }
        }
        vector<int> w(m);
        for (int i = 0; i < m; i++) {
            w[i] = taken[i] ? ed[i].c : -ed[i].c;
        }
        vector<pair<int, int>> d(m, {INF, 0});
        for (int i = 0; i < m; i++) {
            if (type[i] & 1) d[i] = {w[i], 0};
        }
        vector<int> pr(m, -1);
        while (1) {
            vector<pair<int, int>> nd = d;
            for (int i = 0; i < m; i++) {
                if (d[i].first == INF) continue;
                for (int to : e[i]) {
                    if (nd[to] > make_pair(d[i].first + w[to], d[i].second + 1)) {
                        nd[to] = make_pair(d[i].first + w[to], d[i].second + 1);
                        pr[to] = i;
                    }
                }
            }
            if (d == nd) break;
            d = nd;
        }
        int v = -1;
        for (int i = 0; i < m; i++) {
            if ((d[i].first < INF && (type[i] & 2)) && (v == -1 || d[i] < d[v])) v = i;
        }
        if (v == -1) break;
        while (v != -1) {
            sum += w[v];
            taken[v] ^= 1;
            v = pr[v];
        }
        ans[--cnt] = sum;
    }
