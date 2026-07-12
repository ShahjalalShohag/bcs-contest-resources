#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;

// Alternative correct: same greedy, but the XOR-minimizing trie is a pointer-node structure.
// query() returns the smallest v with (x ^ v) not yet inserted, using subtree sizes to skip
// exhausted branches.
struct Trie {
  int B;
  struct node {
    node* nxt[2];
    int sz;
    node() {
      nxt[0] = nxt[1] = NULL;
      sz = 0;
    }
  } *root;
  Trie(int B) : B(B) {
    root = new node();
  }
  void insert(ll val) {
    node* cur = root;
    cur -> sz++;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur -> nxt[b] == NULL) cur -> nxt[b] = new node();
      cur = cur -> nxt[b];
      cur -> sz++;
    }
  }
  ll query(ll x) { // smallest v such that (x ^ v) is not present
    node* cur = root;
    ll v = 0;
    for (int i = B - 1; i >= 0; i--) {
      int b = x >> i & 1;                // taking b keeps this bit of v at 0
      ll full = 1LL << i;               // number of leaves under a child at this level
      node* c = cur -> nxt[b];
      int take = (c == NULL || c -> sz < full) ? b : (b ^ 1);
      if (take != b) v |= 1LL << i;
      cur = cur -> nxt[take];
      if (cur == NULL) return v;        // a free leaf lies below; the rest of v stays 0
    }
    return v;
  }
  void del(node* cur) {
    for (int i = 0; i < 2; i++) if (cur -> nxt[i]) del(cur -> nxt[i]);
    delete(cur);
  }
  ~Trie() {
    del(root);
  }
};

void solve() {
  int n; ll k;
  cin >> n >> k;
  vector<ll> a(n);
  for (auto &x : a) cin >> x;

  ll P = 1LL << k;
  ll ways = 1;
  bool feasible = true;
  for (int i = 1; i <= n; i++) {
    ll term = P - i;
    if (term <= 0) { feasible = false; break; }
    ways = ways * (term % MOD) % MOD;
  }
  if (!feasible) { cout << 0 << '\n'; return; }
  cout << ways << '\n';

  int K = (k == 0) ? 1 : (int)k;
  Trie t(K);
  t.insert(0);                          // C_0 = 0
  ll Cprev = 0;
  for (int i = 0; i < n; i++) {
    ll base = Cprev ^ a[i];
    ll v = t.query(base);
    ll Ci = base ^ v;
    t.insert(Ci);
    Cprev = Ci;
    cout << v << " \n"[i + 1 == n];
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
