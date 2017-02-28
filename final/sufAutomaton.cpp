#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace SA {
    const int MAXN = 1 << 18;
    const int SIGMA = 26;

    int sz, last;
    int nxt[MAXN][SIGMA];
    int link[MAXN], len[MAXN], pos[MAXN];

    void init() {
        memset(nxt, -1, sizeof(nxt));
        memset(link, -1, sizeof(link));
        memset(len, 0, sizeof(len));
        last = 0;
        sz = 1;
    }

    void add(int c) {
        int cur = sz++;
        len[cur] = len[last] + 1;
        pos[cur] = len[cur];
        int p = last;
        last = cur;
        for (; p != -1 && nxt[p][c] == -1; p = link[p]) nxt[p][c] = cur;
        if (p == -1) {
            link[cur] = 0;
            return;
        }
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            return;
        }
        int clone = sz++;
        memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
        len[clone] = len[p] + 1;
        pos[clone] = pos[q];
        link[clone] = link[q];
        link[q] = link[cur] = clone;
        for (; p != -1 && nxt[p][c] == q; p = link[p]) nxt[p][c] = clone;
    }

    int n;
    string s;
    int l[MAXN], r[MAXN];
    int e[MAXN][SIGMA];

    void getSufTree(string _s) {
        memset(e, -1, sizeof(e));
        s = _s;
        n = s.length();
        reverse(s.begin(), s.end());
        init();
        for (int i = 0; i < n; i++) add(s[i] - 'a');
        reverse(s.begin(), s.end());
        for (int i = 1; i < sz; i++) {
            int j = link[i];
            l[i] = n - pos[i] + len[j];
            r[i] = n - pos[i] + len[i];
            e[j][s[l[i]] - 'a'] = i;
        }
    }
}

// timus/1590
int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    string s;
    while (cin >> s) {
        using namespace SA;
        getSufTree(s);
        int ans = 0;
        function<void(int)> dfs = [&](int v) {
            if (v == -1) return;
            ans += r[v] - l[v];
            for (int i = 0; i < SIGMA; i++) dfs(e[v][i]);
        };
        dfs(0);
        cout << ans << endl;
        /*int n = s.length();
        init();
        for (int i = 0; i < n; i++) add(s[i] - 'a');
        
        vector<int> p(sz);
        for (int i = 0; i < sz; i++) p[i] = i;
        sort(p.begin(), p.end(), [&](int i, int j) {
            return len[i] < len[j];
        });

        vector<int> dp(sz);
        for (int i = sz - 1; i >= 0; i--) {
            int v = p[i];
            dp[v] = 1;
            for (int c = 0; c < SIGMA; c++) {
                if (nxt[v][c] != -1) {
                    dp[v] += dp[nxt[v][c]];
                } 
            }
        }
        printf("%d\n", dp[0] - 1);*/
    }

    return 0;
}

