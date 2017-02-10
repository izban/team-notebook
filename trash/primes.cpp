namespace math
{
    const int maxP = 1e6;
    int pp[maxP];
    int p[maxP / 10 + 1000], pc = 0;

    void gen_primes()
    {
        pp[0] = pp[1] = -1;
        for (int i = 2; i < maxP; ++i) pp[i] = i;
        for (int i = 2; i < maxP; ++i)
        {
            if (pp[i] == i) p[pc++] = i;
            for (int j = 0; j < pc && p[j] <= pp[i] && i * p[j] < maxP; ++j) pp[i * p[j]] = p[j];
        }
    }
    bool is_prime(int x)
    {
        if (x < maxP) return pp[x] == x;
        for (int i = 0; p[i] * p[i] <= x; ++i) if (x % p[i] == 0) return false;
        return true;
    }
    // HOW TO USE ::
    // pp[x] <-- smallest prime divisor {x} (or -1 for {x < 2})
    // p[0 .. pc - 1] <-- list of primes < maxP
}
