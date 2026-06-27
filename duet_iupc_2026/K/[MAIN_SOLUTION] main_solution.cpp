#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
using ll = long long;

vector<ll> factorize(ll n) {
  vector<ll> fact;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
        fact.push_back(i);
        while (n % i == 0) n /= i;
    }
  }
  if (n > 1) fact.push_back(n);
  return fact;
}
void solve() {
  ll n; cin >> n;
  if (n == 1) {
    cout << 1 << '\n';
    return;
  }
  auto fact = factorize(n);
  if (fact.size() == 1 and n == fact[0]) {
    cout << 1LL * (n % mod) * (n % mod - 1 + mod) % mod * ((mod + 1) / 2) % mod << '\n';
    return;
  }
  int ans = 0, spf = fact[0];
  for (int k = 1; k < spf; k++) {
    int cur = 1;
    for (auto p: fact) {
        cur = 1LL * cur * ((p - k) % mod) % mod;
    }
    ans = (ans + cur) % mod;
  }
  for (auto p: fact) n /= p;
  ans = 1LL * ans * (n % mod) % mod;
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