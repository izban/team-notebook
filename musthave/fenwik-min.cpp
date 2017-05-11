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

    // indexes 0 .. maxn-1
    // (!) to init fill (a, l, r) with INF
    // (!) modify supports only decreasing of the value
    // find_min [l, r] (both inclusive)
}
