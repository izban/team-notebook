ll mul( ll a, ll b, ll m ) { // works for MOD 8e18
    ll k = (ll)((long double)a * b / m);
    ll r = a * b - m * k;
    if (r < 0) r += m;
    if (r >= m) r -= m;
    return r;
}

