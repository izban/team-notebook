#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace math {
    const int MOD = 1000 * 1000 * 1000 + 7;
    const int N = (int)1.01e6;

    int fct[N], ofct[N];
    char ispr[N];
    vector<int> pr;

    void add(int &a, int b) {
        a = (a + b) % MOD;
    }

    int getC(int n, int k) {
        if (k < 0 || n < k || n < 0) return 0;
        return 1LL * fct[n] * ofct[k] % MOD * ofct[n - k] % MOD;
    }

    int bin(int a, int n) {
        int res = 1;
        while (n) {
            if (n & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            n >>= 1;
        }
        return res;
    }

    int inv(int x) {
        return bin(x, MOD - 2);
    }
    
    // slower, but works for non-prime modulo m
    int rev(int x, int m) {
        if (x == 1) return 1;
        return (1 - rev(m % x, x) * (ll)m) / x + m;
    }

    void init() {
        fct[0] = 1;
        for (int i = 1; i < N; i++) fct[i] = 1LL * fct[i - 1] * i % MOD;
        ofct[N - 1] = inv(fct[N - 1]);
        for (int i = N - 2; i >= 0; i--) ofct[i] = 1LL * ofct[i + 1] * (i + 1) % MOD;

        memset(ispr, 1, sizeof(ispr));
        for (int i = 2; i < N; i++) {
            if (!ispr[i]) continue;
            pr.push_back(i);
            for (int j = i + i; j < N; j += i) ispr[j] = 0;
        }
    }

    bool isPrime(int x) {
        if (x < N) return ispr[x];
        for (int i = 0; i < (int)pr.size() && 1LL * pr[i] * pr[i] <= x; i++) {
            if (x % pr[i] == 0) {
                return 0;
            }
        }
        return 1;
    }
}

using namespace math;

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif

    init();
    
#ifdef HOME
    cerr << "time: " << clock() / (double)CLOCKS_PER_SEC << endl;
#endif
    return 0;
}
