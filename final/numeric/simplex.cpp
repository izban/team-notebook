vector<double> simplex(vector<vector<double> > a) {
    int n = a.size() - 1;
    int m = a[0].size() - 1;
    vector<int> left(n + 1), up(m + 1);
    iota(up.begin(), up.end(), 0);
    iota(left.begin(), left.end(), m);
    auto pivot = [&](int x, int y) {
        swap(left[x], up[y]);
        double k = a[x][y];
        a[x][y] = 1;
        vector<int> vct;
        for (int j = 0; j <= m; j++) {
            a[x][j] /= k;
            if (!eq(a[x][j], 0)) vct.push_back(j);
        }
        for (int i = 0; i <= n; i++) {
            if (eq(a[i][y], 0) || i == x) continue;
            k = a[i][y];
            a[i][y] = 0;
            for (int j : vct) a[i][j] -= k * a[x][j];
        }
    };
    while (1) {
        int x = -1;
        for (int i = 1; i <= n; i++) if (ls(a[i][0], 0) && (x == -1 || a[i][0] < a[x][0])) x = i;
        if (x == -1) break;
        int y = -1;
        for (int j = 1; j <= m; j++) if (ls(a[x][j], 0) && (y == -1 || a[x][j] < a[x][y])) y = j;
        if (y == -1) assert(0); // infeasible
        pivot(x, y);
    }
    while (1) {
        int y = -1;
        for (int j = 1; j <= m; j++) if (ls(0, a[0][j]) && (y == -1 || a[0][j] > a[0][y])) y = j;
        if (y == -1) break;
        int x = -1;
        for (int i = 1; i <= n; i++) if (ls(0, a[i][y]) && (x == -1 || a[i][0] / a[i][y] < a[x][0] / a[x][y])) x = i;
        if (x == -1) assert(0); // unbounded
        pivot(x, y);
    }
    vector<double> ans(m + 1);
    for (int i = 1; i <= n; i++) if (left[i] <= m) ans[left[i]] = a[i][0];
    ans[0] = -a[0][0];
    return ans;
}
// j=1..m: x[j]>=0
// i=1..n: sum(j=1..m) A[i][j]*x[j] <= A[i][0]
// max sum(j=1..m) A[0][j]*x[j]
// res[0] is answer
// res[1..m] is certificate
