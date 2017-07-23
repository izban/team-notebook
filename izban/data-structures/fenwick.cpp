#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct fenwick {
    int n;
    vector<T> f;

    fenwick() {}

    fenwick(int N) {
        n = N;
        f.assign(N, T(0));
    }

    fenwick(vector<T> a) {
        n = a.size();
        for (int i = 0; i < n; i++) add(i, a[i]);
    }

    void add(int x, T y) {
        for (; x < n; x |= x + 1) f[x] += y;
    }

    T get(int x) {
        T res(0);
        for (; x >= 0; x = (x & (x + 1)) - 1) res += f[x];
        return res;
    }

    T get(int l, int r) {
        return get(r) - get(l - 1);
    }

    // return min i: sum(0, i) > x
    int upper_bound(T x) {
        int k = 1;
        while (2 * k <= n) k *= 2;

        int res = 0;
        while (k > 0) {
            if (f[res + k - 1] <= x) {
                x -= f[res + k - 1];
                res += k;
            }
            k /= 2;
        } 
        return res;
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

