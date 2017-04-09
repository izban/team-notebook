struct poly
{
    vi v;
    poly() {}
    poly(vi vv)
    {
        v = vv;
    }
    int size()
    {
        return (int)v.size();
    }
    poly cut(int maxLen)
    {
        if (maxLen < sz(v)) v.resize(maxLen);
        return *this;
    }
    poly norm()
    {
        while (sz(v) > 1 && v.back() == 0) v.pop_back();
        return *this;
    }
    inline int& operator [] (int i)
    {
        return v[i];
    }         
    void out(string name="")
    {
        stringstream ss;
        if (sz(name)) ss << name << "=";
        int fst = 1;
        forn(i, sz(v)) if (v[i])
        {
            int x = v[i];
            int sgn = 1;
            if (x > mod / 2) x = mod-x, sgn = -1;
            if (sgn == -1) ss << "-";
            else if (!fst) ss << "+";
            fst = 0;
            if (!i || x != 1)
            {
                ss << x;
                if (i > 0) ss << "*x";
                if (i > 1) ss << "^" << i;
            }
            else
            {
                ss << "x";
                if (i > 1) ss << "^" << i;
            }
        }
        if (fst) ss <<"0";
        string s;
        ss >> s;
        eprintf("%s\n", s.data());
    }
};

poly operator + (poly A, poly B)
{
    poly C;
    C.v = vi(max(sz(A), sz(B)));
    forn(i, sz(C))
    {
        if (i < sz(A)) C[i] = (C[i] + A[i]) % mod;
        if (i < sz(B)) C[i] = (C[i] + B[i]) % mod;
    }
    return C.norm();
}

poly operator - (poly A, poly B)
{
    poly C;
    C.v = vi(max(sz(A), sz(B)));
    forn(i, sz(C))
    {
        if (i < sz(A)) C[i] = (C[i] + A[i]) % mod;
        if (i < sz(B)) C[i] = (C[i] + mod - B[i]) % mod;
    }
    return C.norm();
}

poly operator * (poly A, poly B)
{
    poly C;
    C.v = vi(sz(A) + sz(B) - 1);

    forn(i, sz(A)) fft::A[i] = A[i];
    forn(i, sz(B)) fft::B[i] = B[i];
    fft::multMod(sz(A), sz(B), mod);
    forn(i, sz(C)) C[i] = fft::C[i];
    return C.norm();
}

poly inv(poly A, int n) // returns A^-1 mod x^n
{
    assert(sz(A) && A[0] != 0);
    A.cut(n);

    auto cutPoly = [](poly &from, int l, int r)
    {
        poly R;
        R.v.resize(r - l);
        for (int i = l; i < r; ++i)
        {
            if (i < sz(from)) R[i - l] = from[i];
        }
        return R;
    };

    function<int(int, int)> rev = [&rev](int x, int m)->int
    {
        if (x == 1) return 1;
        return (1 - rev(m % x, x) * (ll)m) / x + m;
    };

    poly R({rev(A[0], mod)});
    for (int k = 1; k < n; k <<= 1)
    {
        poly A0 = cutPoly(A, 0, k);
        poly A1 = cutPoly(A, k, 2 * k);
        poly H = A0 * R;
        H = cutPoly(H, k, 2 * k);
        poly R1 = (((A1 * R).cut(k) + H) * (poly({0}) - R)).cut(k);
        R.v.resize(2 * k);
        forn(i, k) R[i + k] = R1[i];
    }
    return R.cut(n).norm();
}

pair<poly, poly> divide(poly A, poly B)
{
    if (sz(A) < sz(B)) return {poly({0}), A};
    
    auto rev = [](poly f)
    {
        reverse(all(f.v));
        return f;
    };

    poly q = rev((inv(rev(B), sz(A) - sz(B) + 1) * rev(A)).cut(sz(A) - sz(B) + 1));
    poly r = A - B * q;

    return {q, r};
}
