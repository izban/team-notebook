int n;
char s[N];
int p[N], pn[N], c[N], cn[N], cnt[N];
int o[N];
int lcp[N];

void build() {
    for (int i = 0; i < 256; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[(int)s[i]]++;
    for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) p[--cnt[(int)s[i]]] = i;
    int cl = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        cl += s[p[i]] != s[p[i - 1]];
        c[p[i]] = cl - 1;
    }

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < cl; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[c[i]]++;
        for (int i = 1; i < cl; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) pn[i] = (p[i] - len + n) % n;
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cl = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            cl += c[p[i]] != c[p[i - 1]] || c[(p[i] + len) % n] != c[(p[i - 1] + len) % n];
            cn[p[i]] = cl - 1;
        }
        for (int i = 0; i < n; i++) c[i] = cn[i];
    }

    for (int i = 0; i < n; i++) o[p[i]] = i;

    int z = 0;
    for (int i = 0; i < n; i++) {
        int j = o[i];
        if (j == n - 1) {
            z = 0;
        } else {
            while (s[i + z] == s[p[j + 1] + z]) z++;
        }
        lcp[j] = z;
        z -= !!z; 
    }
}

