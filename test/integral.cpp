#include <cstdio>
#include <cstdlib>
#include <cmath>

typedef long double dbl;

const int maxN = 10;
dbl l, r, a[maxN], b[maxN + 1];
                     
dbl F( dbl x ) {
  dbl cx = (l + r) * 0.5 + (r - l) * 0.5 * x;
  dbl f = 0;
  for (int i = maxN - 1; i >= 0; i--)
    f = f * cx + a[i];
  return f;
}

dbl Simple() { return F(0); }
dbl Simpson() { return (F(-1) + 4 * F(0) + F(1)) / 6; }
dbl Runge2() { return (F(-sqrtl(1.0 / 3)) + F(sqrtl(1.0 / 3))) / 2; }
dbl Runge3() { return (F(-sqrtl(3.0 / 5)) * 5 + F(0) * 8 + F(sqrtl(3.0 / 5)) * 5) / 18; }

const int N = 30;

typedef dbl (*func)();

dbl Int( func f, dbl L, dbl R ) {
  dbl sum = 0, dx = (R - L) / N;
  for (int i = 0; i < N; i++)
    l = L + i * dx, r = l + dx, sum += f();
  return sum * (R - L) / N;
}

dbl FB( dbl cx ) {
  dbl f = 0;
  for (int i = maxN; i >= 0; i--)
    f = f * cx + b[i];
  return f;
}

dbl Answer( dbl L, dbl R ) {
  for (int i = 1; i <= maxN; i++)
    b[i] = a[i - 1] / i;
  return FB(R) - FB(L);
}                     

int main() {
  func f[] = {Simple, Simpson, Runge2, Runge3};
  const char *s[] = {"Simple", "Simpson", "Runge2", "Runge3"};
  int fn = sizeof(f) / sizeof(f[0]);

  for (int n = 2; n <= maxN; n++) {
    for (int i = 0; i < n; i++)
      a[i] = 0.5 + 0.5 * rand() / RAND_MAX;
    printf("n = %02d", n);
    dbl ans = Answer(0, 1);
    for (int i = 0; i < fn; i++)
      printf(", %s = %12g", s[i], fabs(Int(f[i], 0, 1) - ans));
    puts("");
  }
}
