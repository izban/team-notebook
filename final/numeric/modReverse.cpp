int rev(int x, int m) {
    if (x == 1) return 1;
    return (1 - rev(m % x, x) * (ll)m) / x + m;
}
