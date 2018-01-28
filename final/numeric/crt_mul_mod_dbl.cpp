int rev(int x, int m)
{
    if (x == 1) return 1;
    return (1 - rev(m % x, x) * (ll)m) / x + m;
}

int CRT(int a1, int m1, int a2, int m2)
{
    return (a1 - a2 % m1 + m1) * (ll)rev(m2, m1) % m1 * m2 + a2;
}

ll mul( ll a, ll b, ll m ) { // works for MOD 8e18
    ll k = (ll)((long double)a * b / m);
    ll r = a * b - m * k;
    if (r < 0) r += m;
    if (r >= m) r -= m;
    return r;
}
