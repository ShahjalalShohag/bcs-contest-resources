#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
using ll = long long;

int power(int n, long long k) {
  int ans = 1 % mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> cnt(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }
  if (k == 1) {
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += 1LL * i * cnt[i];
    ans %= mod;
    cout << ans << '\n';
    return;
  }
  --k;
  vector<int> ncr(21, 0);
  ncr[0] = 1;
  for (int i = 1; i <= min(k, 20); i++) {
    ncr[i] = 1LL * ncr[i - 1] * (k - i + 1) % mod;
    ncr[i] = 1LL * ncr[i] * power(i, mod - 2) % mod;
  }
  vector<int> f(n + 1, 0), tot(n + 1, 0);
  tot[1] = power(cnt[1], k); // all 1s
  f[1] = 1;
  for (int x = 1; x <= min(20, k); x++) {
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      for (int j = 2; i * j <= n; j++) {
        g[i * j] += 1LL * f[i] * cnt[j] % mod;
        g[i * j] %= mod;
      }
    }
    f = g;
    for (int i = 2; i <= n; i++) if (f[i]) {
        tot[i] += 1LL * ncr[x] * power(cnt[1], k - x) % mod * f[i] % mod; // x non-1s and (k - x) 1s
        tot[i] %= mod;
      }
  }
  for (int i = 1; i <= n; i++) tot[i] += tot[i - 1], tot[i] %= mod;
  int ans = 0;
  for (int i = 1; i <= n; i++) if (cnt[i]) {
    for (int l = 1, r; l <= i; l = r + 1) {
      int x = i / l;
      r = i / x;
      ans += 1LL * (tot[r] - tot[l - 1] + mod) * x % mod * cnt[i] % mod;
      ans %= mod;
    }
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