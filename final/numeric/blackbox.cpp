namespace blackbox
{
    int A[N];
    int B[N];
    int C[N];
    
    int magic(int k, int x)
    {
        B[k] = x;
        C[k] = (C[k] + A[0] * (ll)B[k]) % mod;
        int z = 1;
        if (k == N - 1) return C[k];
        while ((k & (z - 1)) == (z - 1))
        {
            //mult B[k - z + 1 ... k] x A[z .. 2 * z - 1]
            forn(i, z) fft::A[i] = A[z + i];
            forn(i, z) fft::B[i] = B[k - z + 1 + i];
            fft::multMod(z, z, mod);
            forn(i, 2 * z - 1) C[k + 1 + i] = (C[k + 1 + i] + fft::C[i]) % mod;
            z <<= 1;
        }
        return C[k];
    }        
    // A -- constant array
    // magic(k, x):: B[k] = x, returns C[k]
    // !! WARNING !! better to set N twice the size needed
}
