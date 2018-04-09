function<dbl(dbl, dbl, function<dbl(dbl)>)> f = [&](dbl L, dbl R, function<dbl(dbl)> g) {
    const int ITERS = 1000000;
    dbl ans = 0;
    dbl step = (R - L) * 1.0 / ITERS;
    for (int it = 0; it < ITERS; it++) {
        double xl = L + step * it;
        double xr = L + step * (it + 1);
        dbl x1 = (xl + xr) / 2;
        dbl x0 = x1 - (x1 - xl) * sqrt(3.0 / 5);
        dbl x2 = x1 + (x1 - xl) * sqrt(3.0 / 5);
        ans += (5 * g(x0) + 8 * g(x1) + 5 * g(x2)) / 18 * step;
    }
    return ans;
};
