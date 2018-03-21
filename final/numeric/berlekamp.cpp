vector<int> berlekamp(vector<int> s) {
    int l = 0;
    vector<int> la(1, 1);
    vector<int> b(1, 1);
    for (int r = 1; r <= (int)s.size(); r++) {
        int delta = 0;
        for (int j = 0; j <= l; j++) {
            delta = (delta + 1LL * s[r - 1 - j] * la[j]) % MOD;
        }
        b.insert(b.begin(), 0);
        if (delta != 0) {
            vector<int> t(max(la.size(), b.size()));
            for (int i = 0; i < (int)t.size(); i++) {
                if (i < (int)la.size()) t[i] = (t[i] + la[i]) % MOD;
                if (i < (int)b.size()) t[i] = (t[i] - 1LL * delta * b[i] % MOD + MOD) % MOD;
            }
            if (2 * l <= r - 1) {
                b = la;
                int od = inv(delta);
                for (int &x : b) x = 1LL * x * od % MOD;
                l = r - l;
            }
            la = t;
        }
    }
    assert((int)la.size() == l + 1);
    assert(l * 2 + 30 < (int)s.size());
    reverse(la.begin(), la.end());
    return la;
}

vector<int> mul(vector<int> a, vector<int> b) {
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % MOD;
        }
    }
    vector<int> res(c.size());
    for (int i = 0; i < (int)res.size(); i++) res[i] = c[i] % MOD;
    return res;
}

vector<int> mod(vector<int> a, vector<int> b) {
    if (a.size() < b.size()) a.resize(b.size() - 1);

    int o = inv(b.back());
    for (int i = (int)a.size() - 1; i >= (int)b.size() - 1; i--) {
        if (a[i] == 0) continue;
        int coef = 1LL * o * (MOD - a[i]) % MOD;
        for (int j = 0; j < (int)b.size(); j++) {
            a[i - (int)b.size() + 1 + j] = (a[i - (int)b.size() + 1 + j] + 1LL * coef * b[j]) % MOD;
        }
    }
    while (a.size() >= b.size()) {
        assert(a.back() == 0);
        a.pop_back();
    }
    return a;
}

vector<int> bin(int n, vector<int> p) {
    vector<int> res(1, 1);
    vector<int> a(2); a[1] = 1;
    while (n) {
        if (n & 1) res = mod(mul(res, a), p);
        a = mod(mul(a, a), p);
        n >>= 1;
    }
    return res;
}

int f(vector<int> t, int m) {
    vector<int> v = berlekamp(t);
    vector<int> o = bin(m - 1, v);
    int res = 0;
    for (int i = 0; i < (int)o.size(); i++) res = (res + 1LL * o[i] * t[i]) % MOD;
    return res;
}
