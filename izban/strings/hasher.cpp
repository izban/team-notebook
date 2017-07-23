#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//typedef long long Hash;

const int K = 2;
const int MOD[K] = {(int)1e9 + 7, (int)1e9 + 9};
struct Hash {
    int a[K];

    Hash() {
        fill(a, a + K, 0);
    }

    Hash(int x) {
        fill(a, a + K, x);
    }

    Hash operator- (const Hash &h) const {
        Hash res;
        for (int i = 0; i < K; i++) {
            res.a[i] = (a[i] - h.a[i] + MOD[i]) % MOD[i];
        }
        return res;
    }
    
    Hash operator+ (const Hash &h) const {
        Hash res;
        for (int i = 0; i < K; i++) {
            res.a[i] = (a[i] + h.a[i]) % MOD[i];
        }
        return res;
    }
    
    Hash operator* (const Hash &h) const {
        Hash res;
        for (int i = 0; i < K; i++) {
            res.a[i] = (1LL * a[i] * h.a[i]) % MOD[i];
        }
        return res;
    }

    bool operator< (const Hash &h) const {
        for (int i = 0; i < K; i++) {
            if (a[i] != h.a[i]) return a[i] < h.a[i];
        }
        return 0;
    }

    bool operator== (const Hash &h) const {
        for (int i = 0; i < K; i++) {
            if (a[i] != h.a[i]) return 0;
        }
        return 1;
    }

    bool operator!= (const Hash &h) const {
        return !(*this == h);
    }
};


const Hash Q = Hash(239);
const int N = (int)1.01e6;
Hash p[N];
bool inited = 0;
void init() {
    if (inited) return;
    inited = 1;
    p[0] = Hash(1);
    for (int i = 1; i < N; i++) p[i] = p[i - 1] * Q;
}
struct Hasher {
    int n;
    string s;
    vector<Hash> h;
    vector<Hash> hr;

    Hasher() {}
    Hasher(string _s) {
        init();
        s = _s;
        n = s.length();
        h.resize(n + 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = h[i] + p[i] * s[i];
        }
        hr.resize(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            hr[i] = hr[i + 1] + p[n - 1 - i] * s[i];
        }
    }

    Hash getHash(int l, int r) {
        if (l <= r) {
            return (h[r + 1] - h[l]) * p[N - 1 - l];
        } else {
            return (hr[l] - hr[r + 1]) * p[N - (n - r)];
        }
    }

    int lcp(int i, int j) {
        if (i > j) swap(i, j);
        int L = 0, R = n - j + 1;
        while (R - L > 1) {
            int M = (L + R) >> 1;
            if (getHash(i, i + M - 1) == getHash(j, j + M - 1)) L = M;
            else R = M;
        }
        return L;
    }

    int compare(int i, int j) {
        int w = lcp(i, j);
        char ci = i + w == n ? 0 : s[i + w];
        char cj = j + w == n ? 0 : s[j + w];
        if (ci < cj) return -1;
        if (ci > cj) return 1;
        return 0;
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


