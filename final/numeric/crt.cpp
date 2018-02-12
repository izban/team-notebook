int CRT(int a1, int m1, int a2, int m2) {
    return (a1 - a2 % m1 + m1) * (ll)rev(m2, m1) % m1 * m2 + a2;
}
