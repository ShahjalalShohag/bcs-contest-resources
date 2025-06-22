#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 21, mod = 998244353, P = 1000003, Q = 1000039;
using ll = long long;

const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1) {
  for (; y; y >>= 1, x = (long long) x * x % mod) if (y & 1) ans = (long long) ans * x % mod;
  return ans;
}
void precompute(int len) {
  lim = wn[0] = 1; int s = -1;
  while (lim < len) lim <<= 1, ++s;
  for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
  const int g = POW(root, (mod - 1) / lim);
  inv_lim = POW(lim, mod - 2);
  for (int i = 1; i < lim; ++i) wn[i] = (long long) wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ) {
  for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
    for (int j = 0; j < lim; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        const int x = a[k + j], y = (long long) a[k + j + i] * w[k] % mod;
        reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
      }
    }
  }
  if (!typ) {
    reverse(a.begin() + 1, a.begin() + lim);
    for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * inv_lim % mod;
  }
}
vector<int> multiply(vector<int> f, vector<int> g) {
  if (f.empty() or g.empty()) return {};
  int n = (int)f.size() + (int)g.size() - 1;
  if (n == 1) return {(int)((long long) f[0] * g[0] % mod)};
  precompute(n);
  vector<int> a = f, b = g;
  a.resize(lim); b.resize(lim);
  ntt(a, 1), ntt(b, 1);
  for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * b[i] % mod;
  ntt(a, 0);
  a.resize(n + 1);
  return a;
}

vector<int> solve(vector<int> a) {
  int n = a.size();
  a.resize(3 * n);
  for (int i = 0; i < n; i++) {
    a[i + n] = a[i + 2 * n] = a[i];
  }
  auto c = multiply(a, a);
  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x = c[2 * i - 1 + n];
    if (i) x = (x - c[2 * i - 1] + mod) % mod;
    v.push_back(x);
  }
  return v;
}

int power(int n, int k, const int mod) {
  int ans = 1 % mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}

int get_hash(int x) {
  return power(P, power(Q, x, mod - 1), mod);
}

void solve() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  vector<int> c(n), d(n);
  for (int i = 0; i < n; i++) {
    c[i] = get_hash(a[i]);
  }
  for (int i = 0; i < n; i++) {
    d[i] = get_hash(b[i]);
  }
  auto u = solve(c);
  map<tuple<int, int>, int> mp;
  for (int i = 0; i < n; i++) {
    int y = n % 2 == 1 ? a[(n / 2 + i) % n] : -1;
    mp[make_tuple(u[i], y)]++;
  }
  auto v = solve(d);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int y = n % 2 == 1 ? b[(n / 2 + i) % n] : -1;
    ans += mp[make_tuple(v[i], y)];
  }
  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}