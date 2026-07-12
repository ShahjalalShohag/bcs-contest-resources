// Same answer via recursive inclusion-exclusion for C (pruning products past n), then the fixed
// colors: strip each fixed integer to its core and parity, group by core, subtract one exponent
// per pinned core, and output 0 if two pins in a core disagree.
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998244353;

ll power(ll a, ll b) {
  a %= MOD; if (a < 0) a += MOD;
  ll r = 1;
  while (b > 0) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
  return r;
}

int k;
vector<ll> p;
ll n, C;

void dfs(int i, ll prod, int sign) {
  if (i == k) { C += sign * (n / prod); return; }
  dfs(i + 1, prod, sign);
  if (prod <= n / p[i]) dfs(i + 1, prod * p[i], -sign);
}

void solve() {
  cin >> n >> k;
  p.assign(k, 0);
  for (auto &x : p) cin >> x;
  C = 0;
  dfs(0, 1, 1);

  int m; cin >> m;
  map<ll, int> base;
  bool conflict = false;
  ll D = 0;
  for (int i = 0; i < m; i++) {
    ll v; int c; cin >> v >> c;
    int parity = 0;
    for (int j = 0; j < k; j++) while (v % p[j] == 0) { v /= p[j]; parity ^= 1; }
    int b = c ^ parity;
    auto it = base.find(v);
    if (it == base.end()) { base[v] = b; D++; }
    else if (it->second != b) conflict = true;
  }

  cout << (conflict ? 0 : power(2, C - D)) << "\n";
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
