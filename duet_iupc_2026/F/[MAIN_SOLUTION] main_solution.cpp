#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;

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
    ll n, m; cin >> n >> m;
    int x = n % mod;
    int ans = 0, ones_above = 0;
    for (int b = 62; b >= 0; b--) {
        if ((m >> b) & 1) {
            ans = (ans + 1LL * power(x, ones_above) * power((1 + x) % mod, b) % mod) % mod;
            ones_above++;
        }
    }
    ans = (ans + power(x, ones_above)) % mod;
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