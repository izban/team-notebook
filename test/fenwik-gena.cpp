/**
 *    author:  [itmo] enot110
 *    created: 11.05.2017 14:55:26       
**/
#include <bits/stdc++.h>

#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define pw(x) (1LL<<(x))

using namespace std;

typedef double dbl;

const int inf = 1.01e9;
const int maxn = 1e5;

namespace fenwik
{
    const int N = maxn + 1;

    int a[N], l[N], r[N];

    void modify(int q, int v) {
      q++;
      a[q] = min(a[q], v);
      int x = q;
      while (x < N) {          
        l[x] = min(l[x], v);
        x = (x | (x - 1)) + 1;
      }
      x = q;
      while (x > 0) {
        r[x] = min(r[x], v);
        x &= x - 1;
      }
    }

    int find_min(int ll, int rr) {
      ll++;
      rr++;
      int res = inf;
      int x = ll;
      while ((x | (x - 1)) + 1 <= rr) {
        res = min(res, r[x]);
        x = (x | (x - 1)) + 1;
      }
      res = min(res, a[x]);
      x = rr;
      while ((x & (x - 1)) >= ll) {
        res = min(res, l[x]);
        x &= x - 1;
      }
      return res;
    }
}


const int N = 1 << 17;
int t[2 * N];

void upd(int x, int val)
{
    x += N;
    t[x] = min(t[x], val);
    while (x > 1)
    {
        x >>= 1;
        t[x] = min(t[2 * x], t[2 * x + 1]);
    }
}

int get(int l, int r)
{
    l += N;
    r += N;
    int res = inf;
    while (l <= r)
    {
        if (l & 1) res = min(res, t[l]);
        if (!(r & 1)) res = min(res, t[r]);
        l = (l + 1) >> 1;
        r = (r - 1) >> 1;
    }
    return res;
}

                
dbl TIME()
{
    return (dbl)clock() * 1. / CLOCKS_PER_SEC;
}


int main()
{
    //init
    forn(i, maxn)
    {
        fenwik::a[i + 1] = fenwik::l[i + 1] = fenwik::r[i + 1] = inf;
    }
    forn(i, 2 * N) t[i] = inf;

    // check correctness

    if (0) {
        int n = 1e2;
        forn(i, n)
        {
            int x = rand();
            printf("upd %d %d\n", i, x);
            upd(i, x);
            fenwik::modify(i, x);
        }
        for (int l = 0; l < n; ++l) for (int r = l; r < n; ++r)
        {
            int m1 = fenwik::find_min(l, r);
            int m2 = get(l, r);
            if (m1 != m2)
            {
                printf("l = %d, r = %d, m1 = %d, m2 = %d\n", l, r, m1, m2);
                exit(0);
            }
        }
        printf("all ok!\n");
    }

    // check time

    int iters = 1e7;

    const int MX = maxn;
    {
        mt19937 rnd(239);
        dbl st = TIME();
        forn(_, iters)
        {
            int x = rnd() % MX;
            int what = rnd() & (pw(29) - 1);
            fenwik::modify(x, what);
        }
        dbl en = TIME();
        printf("fenwik update       = %.3f\n", en - st);
    }

    {
        mt19937 rnd(239);
        dbl st = TIME();
        forn(_, iters)
        {
            int x = rnd() % MX;
            int what = rnd() & (pw(29) - 1);
            upd(x, what);  
        }
        dbl en = TIME();
        printf("segment-tree update = %.3f\n", en - st);
    }

    {
        mt19937 rnd(239);
        dbl st = TIME();
        long long sum = 0;
        forn(_, iters)
        {
            int l = rnd() % MX;
            int r = rnd() % MX;
            if (l > r) swap(l, r);
            int val = fenwik::find_min(l, r);
            sum += val;
        }
        dbl en = TIME();
        printf("fenwik get          = %.3f  (hashsum = %I64d)\n", en - st, sum);
    }
    
    {
        mt19937 rnd(239);
        dbl st = TIME();
        long long sum = 0;
        forn(_, iters)
        {
            int l = rnd() % MX;
            int r = rnd() % MX;
            if (l > r) swap(l, r);
            int val = get(l, r);
            sum += val;
        }
        dbl en = TIME();
        printf("segment-tree get    = %.3f  (hashsum = %I64d)\n", en - st, sum);
    }

    {
        mt19937 rnd(239);
        dbl st = TIME();
        long long sum = 0;
        forn(_, iters)
        {
            int l = rnd() % 1000;
            int r = MX - 1 - rnd() % 1000;
            if (l > r) swap(l, r);
            int val = fenwik::find_min(l, r);
            sum += val;
        }
        dbl en = TIME();
        printf("fenwik get          = %.3f  (hashsum = %I64d)\n", en - st, sum);
    }
    
    {
        mt19937 rnd(239);
        dbl st = TIME();
        long long sum = 0;
        forn(_, iters)
        {
            int l = rnd() % 1000;
            int r = MX - 1 - rnd() % 1000;
            if (l > r) swap(l, r);
            int val = get(l, r);
            sum += val;
        }
        dbl en = TIME();
        printf("segment-tree get    = %.3f  (hashsum = %I64d)\n", en - st, sum);
    }

    return 0;
}
