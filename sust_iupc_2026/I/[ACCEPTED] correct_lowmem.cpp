#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;

// Alternative correct: same greedy, but the high bits are grouped with a std::unordered_map
// and the low-bit trie uses depth 19; an independent implementation for cross-checking.
const int LOW = 19;

vector<array<int,2>> ch;
vector<int> sub;
int nn() { ch.push_back({0, 0}); sub.push_back(0); return (int)ch.size() - 1; }

unordered_map<ll, int> root;

void insert(ll x) {
  int &r = root[x >> LOW];
  if (r == 0) r = nn();
  int u = r;
  for (int b = LOW - 1; b >= 0; b--) {
    int bit = (x >> b) & 1;
    if (ch[u][bit] == 0) ch[u][bit] = nn();
    u = ch[u][bit];
    sub[u]++;
  }
}

ll query(ll base) {
  auto it = root.find(base >> LOW);
  if (it == root.end() || it->second == 0) return 0;
  int u = it->second;
  ll v = 0;
  for (int b = LOW - 1; b >= 0; b--) {
    int want = (base >> b) & 1;
    int c = ch[u][want];
    if (!(c == 0 || sub[c] < (1 << b))) { v |= 1LL << b; want ^= 1; }
    if (ch[u][want] == 0) return v;
    u = ch[u][want];
  }
  return v;
}

void solve() {
  int n; ll k;
  cin >> n >> k;
  vector<ll> a(n);
  for (auto &x : a) cin >> x;

  __int128 P = (__int128)1 << k;
  ll ways = 1;
  bool feasible = true;
  for (int i = 1; i <= n; i++) {
    __int128 term = P - i;
    if (term <= 0) { feasible = false; break; }
    ways = ways * (ll)(term % MOD) % MOD;
  }
  if (!feasible) { cout << 0 << '\n'; return; }
  cout << ways << '\n';

  ch.clear(); sub.clear(); root.clear();
  nn();
  insert(0);
  ll Cprev = 0;
  for (int i = 0; i < n; i++) {
    ll base = Cprev ^ a[i];
    ll b = query(base);
    insert(base ^ b);
    Cprev = base ^ b;
    cout << b << " \n"[i + 1 == n];
  }
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
