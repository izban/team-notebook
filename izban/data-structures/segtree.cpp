#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct segtree {
    int N;
    vector<T> t;
    T zero;
    function<T(T, T)> f;

    segtree() {}
    void init(int n, T _zero, function<T(T, T)> _f) {
        f = _f;
        zero = _zero;
        N = 1;
        while (N < n) N <<= 1;
        t.assign(2 * N, zero);
    }
    segtree(int n, T _zero, function<T(T, T)> _f) {
        init(n, _zero, _f);
    }
    segtree(vector<T> &a, T _zero, function<T(T, T)> _f) {
        int n = a.size();
        init(n, _zero, _f);
        
        for (int i = 0; i < n; i++) t[N + i] = a[i];
        for (int i = N - 1; i > 0; i--) {
            t[i] = f(t[i * 2], t[i * 2 + 1]);
        }
    }

    T get(int l, int r) {
        T res = zero;
        l += N;
        r += N;
        while (l <= r) {
            if (l % 2 == 1) res = f(res, t[l]);
            if (r % 2 == 0) res = f(res, t[r]);
            l = (l + 1) >> 1;
            r = (r - 1) >> 1;
        }
        return res;
    }

    void upd(int x, T y) {
        x += N;
        t[x] = y;
        while (x > 1) {
            x >>= 1;
            t[x] = f(t[x * 2], t[x * 2 + 1]);     
        }
    }
};

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif


    
#ifdef HOME
    cerr << "time: " << clock() / (double)CLOCKS_PER_SEC << endl;
#endif
    return 0;
}


