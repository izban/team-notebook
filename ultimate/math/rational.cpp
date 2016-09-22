struct rat
{
    ll x, y;
    rat() {}
    rat(ll xx, ll yy): x(xx), y(yy) {}
    rat(ll xx): x(xx), y(1) {}
    void norm()
    {
        ll g = __gcd(x, y);
        x /= g;
        y /= g;
        if (y < 0) x = -x, y = -y;
    }
};

inline rat operator + (rat r1, rat r2)
{
    ll g = __gcd(r1.y, r2.y);
    rat res = rat(r1.x * (r2.y / g) + (r1.y / g) * r2.x, r1.y * (r2.y / g));
    res.norm();
    return res;
}

inline rat operator - (rat r1, rat r2)
{
    ll g = __gcd(r1.y, r2.y);
    rat res = rat(r1.x * (r2.y / g) - (r1.y / g) * r2.x, r1.y * (r2.y / g));
    res.norm();
    return res;
}

inline rat operator * (rat r1, rat r2)
{
    ll g1 = __gcd(r1.x, r2.y);
    ll g2 = __gcd(r1.y, r2.x);
    rat res = rat((r1.x / g1) * (r2.x / g2), (r1.y / g2) * (r2.y / g1));
    res.norm();
    return res;
}

inline rat operator / (rat r1, rat r2)
{
    ll g1 = __gcd(r1.x, r2.x);
    ll g2 = __gcd(r1.y, r2.y);
    rat res = rat((r1.x / g1) * (r2.y / g2), (r1.y / g2) * (r2.x / g1));
    res.norm();
    return res;
}

// !!! this comprasions can be made more overflow-safe (but more slow too)
inline bool operator < (rat r1, rat r2) { return r1.x * r2.y < r1.y * r2.x; }
inline bool operator > (rat r1, rat r2) { return r1.x * r2.y > r1.y * r2.x; }
inline bool operator == (rat r1, rat r2) { return r1.x * r2.y == r1.y * r2.x; }
