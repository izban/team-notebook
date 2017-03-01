#include <bits/stdc++.h>
using namespace std;

#include "../final/sufAutomaton.cpp"

// timus/1590
int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    string s;
    while (cin >> s) {
        using namespace SA; getSufTree(s);
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

