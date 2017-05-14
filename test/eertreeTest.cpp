#include <bits/stdc++.h>
using namespace std;

namespace eertree {
    const int INF = 1e9;
    const int N = 5e6 + 10;
    char _s[N];
    char *s = _s + 1;
    int to[N][2];
    int suf[N], len[N];
    int sz, last;

    const int odd = 1, even = 2, blank = 3;

    void go(int &u, int pos) {
        while (u != blank && s[pos - len[u] - 1] != s[pos]) {
            u = suf[u];
        } 
    }

    int add(int pos) {
        go(last, pos);
        int u = suf[last];
        go(u, pos);
        int c = s[pos] - 'a';
        int res = 0;
        if (!to[last][c]) {
            res = 1;
            to[last][c] = sz;
            len[sz] = len[last] + 2;
            suf[sz] = to[u][c];
            sz++;
        }
        last = to[last][c];
        return res;
    }
    
    void init() {
        to[blank][0] = to[blank][1] = even;
        len[blank] = suf[blank] = INF;
        len[even] = 0, suf[even] = odd;
        len[odd] = -1, suf[odd] = blank;
        last = even;
        sz = 4;
    }    
}

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif
    //fgets(eertree::s, (int)5e6, stdin);
    gets(eertree::s);
    int n = strlen(eertree::s);
    string res = "";
    eertree::init();
    for (int i = 0; i < n; i++) {
        res += '0' + eertree::add(i);
    }
    printf("%s\n", res.c_str());
    return 0;
}
