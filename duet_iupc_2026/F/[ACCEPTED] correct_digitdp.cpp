#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;

// Same answer (sum_{M=0}^{m} n^popcount(M)), written as the textbook recursive
// digit DP with a tight/free flag — the form most contestants would code.
// go(pos, tight) = sum over completions of bits pos..0 of x^(ones placed there).
// At each position try digit v in [0, up] (up = the bit of m if tight, else 1),
// weighting the branch by x^v. Free states are memoized. This is structurally
// different from main_solution's iterative accumulation, so it cross-checks it.

ll x;
int L;
int dig[64];      // dig[i] = i-th bit of m (LSB = 0)
ll memo[64];      // memo[pos] = go(pos, tight=false), valid for the current x
bool seen[64];

ll go(int pos, bool tight) {
    if (pos < 0) return 1;
    if (!tight && seen[pos]) return memo[pos];
    int up = tight ? dig[pos] : 1;
    ll res = 0, xv = 1;                       // xv = x^v
    for (int v = 0; v <= up; v++) {
        res = (res + xv * go(pos - 1, tight && (v == up))) % mod;
        xv = xv * x % mod;
    }
    if (!tight) { memo[pos] = res; seen[pos] = true; }
    return res;
}

void solve() {
    ll n, m; cin >> n >> m;
    x = n % mod;
    L = (m == 0) ? 1 : 64 - __builtin_clzll((unsigned long long)m);
    for (int i = 0; i < L; i++) { dig[i] = (m >> i) & 1; seen[i] = false; }
    cout << go(L - 1, true) << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
