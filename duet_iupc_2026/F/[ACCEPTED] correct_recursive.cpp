#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;

// Same answer, different derivation: a highest-bit recurrence for
// S(m) = sum_{M=0}^{m} x^popcount(M).  Let B be the top set bit of m.
//   - numbers in [0, 2^B - 1] : B free bits  -> (1+x)^B
//   - numbers in [2^B, m]      : bit B set, lower part in [0, m-2^B]
//                                -> x * S(m - 2^B)
// Independent of main_solution's iterative DP, so it cross-checks it.

ll power(ll a, ll b) {
    a %= mod; if (a < 0) a += mod;
    ll r = 1;
    while (b) { if (b & 1) r = r * a % mod; a = a * a % mod; b >>= 1; }
    return r;
}

ll x;
ll S(ll m) {
    if (m < 0) return 0;
    if (m == 0) return 1;
    int B = 63 - __builtin_clzll((unsigned long long)m);
    ll high = power((1 + x) % mod, B);
    ll rest = x % mod * S(m - (1LL << B)) % mod;
    return (high + rest) % mod;
}

void solve() {
    ll n, m; cin >> n >> m;
    x = n % mod;
    cout << S(m) << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
