
const int SZ = 6;
const int BASE = pw(SZ);
const int MOD = BASE - 1;

struct Bitset {
    typedef unsigned long long T;
    vector<T> data;
    int n;
    void resize(int nn) {
        n = nn;
        data.resize((n + BASE - 1) / BASE);
    }
    void set(int pos, int val) {
        int id = pos >> SZ;
        int rem = pos & MOD;
        data[id] ^= data[id] & pw(rem);
        data[id] |= val * pw(rem);
    } 
    int get(int pos) {
        return (data[pos >> SZ] >> (pos & MOD)) & 1;
    }
    // k > 0 -> (*this) << k 
    // k < 0 -> (*this) >> (-k)
    Bitset shift (int k) { 
        Bitset res;
        res.resize(n);
        int s = k / BASE;
        int rem = k % BASE;
        if (rem < 0) {
            rem += BASE;
            s--;
        }
        int p1 = BASE - rem;
        T mask = (p1 == 64)? -1: pw(p1) - 1;
        for (int i = max(0, -s); i < sz(data) - max(s, 0); i++) {
            res.data[i + s] |= (data[i] & mask) << rem;
        }
        if (rem != 0) {
            for (int i = max(0, -s - 1); i < sz(data) - max(s + 1, 0); i++) {
                res.data[i + s + 1] |= (data[i] >> p1) & (pw(rem) - 1);
            }
        }
        int cc = data.size() * BASE - n;
        res.data.back() <<= cc;
        res.data.back() >>= cc;
        return res;
    }
};

