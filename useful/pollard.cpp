namespace pollard
{
    using math::p;

    vector<pair<ll, int>> getFactors(ll N)
    {
        vector<ll> primes;

        const int MX = 1e5;
        const ll MX2 = MX * (ll)MX;

        assert(MX <= math::maxP && math::pc > 0);
    
        function<void(ll)> go = [&go, &primes](ll n)
        {
            for (ll x : primes) while (n % x == 0) n /= x;
            if (n == 1) return;
            if (n > MX2)
            {
                auto F = [&](ll x) {
                    ll k = ((long double)x * x) / n;
                    ll r = (x * x - k * n + 3) % n;
                    return r < 0 ? r + n : r;
                };
                ll x = mt19937_64()() % n, y = x;
                const int C = 3 * pow(n, 0.25);

                ll val = 1;
                forn(it, C)
                {
                    x = F(x), y = F(F(y));
                    if (x == y) continue;
                    ll delta = abs(x - y);
                    ll k = ((long double)val * delta) / n;
                    val = (val * delta - k * n) % n;
                    if (val < 0) val += n;
                    if (val == 0)
                    {
                        ll g = __gcd(delta, n);
                        go(g), go(n / g);
                        return;
                    }
                    if ((it & 255) == 0)
                    {
                        ll g = __gcd(val, n);
                        if (g != 1)
                        {
                            go(g), go(n / g);
                            return;
                        }
                    }
                }
            }
            primes.pb(n);
        };

        ll n = N;

        for (int i = 0; i < math::pc && p[i] < MX; ++i) if (n % p[i] == 0)
        {
            primes.pb(p[i]);
            while (n % p[i] == 0) n /= p[i];
        }

        go(n);

        sort(primes.begin(), primes.end());

        vector<pair<ll, int>> res;
        for (ll x : primes)
        {
            int cnt = 0;
            while (N % x == 0)
            {
                cnt++;
                N /= x;
            }
            res.push_back({x, cnt});
        }
        return res;
    }
}
