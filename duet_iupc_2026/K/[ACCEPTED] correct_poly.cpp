#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;
const int LIM = 1000000;

vector<int> primes;

void sieve() {
    vector<bool> is(LIM + 1, true);
    is[0] = is[1] = false;
    for (int i = 2; i <= LIM; i++) if (is[i]) {
        primes.push_back(i);
        for (int j = 2 * i; j <= LIM; j += i) is[j] = false;
    }
}

ll pw(ll a, ll b) {
    a %= MOD; if (a < 0) a += MOD;
    ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}

// Same answer as main, computed by a different method: the partial sum
// T(m) = sum_{k=1}^{m} prod_i (p_i - k) is a polynomial in m of degree r+1, so we
// sample it at m = 0..r+1 and Lagrange-interpolate to m = pmin-1. O(r^2) per test,
// independent of pmin.
int main() {
    sieve();
    int t;
    scanf("%d", &t);
    while (t--) {
        ll n;
        scanf("%lld", &n);

        vector<ll> ps;
        ll m = n;
        for (int p : primes) {
            if ((ll)p * p > m) break;
            if (m % p == 0) { ps.push_back(p); while (m % p == 0) m /= p; }
        }
        if (m > 1) ps.push_back(m);

        ll P = 1; for (ll p : ps) P *= p;
        ll q = n / P;
        if (ps.empty()) { printf("1\n"); continue; } // n = 1: only the interval [1, 1]
        int r = (int)ps.size();
        ll pmin = ps[0];

        int d = r + 1;            // degree of T(m)
        vector<ll> T(d + 1);      // T[j] = T(j) for j = 0..d
        T[0] = 0;
        for (int j = 1; j <= d; j++) {
            ll g = 1;
            for (ll p : ps) g = g * (((p - j) % MOD + MOD) % MOD) % MOD;
            T[j] = (T[j - 1] + g) % MOD;
        }

        ll S;
        if (pmin - 1 <= d) {
            S = T[pmin - 1];
        } else {
            ll X = (pmin - 1) % MOD;
            vector<ll> pre(d + 2), suf(d + 2), fact(d + 1);
            pre[0] = 1;
            for (int i = 0; i <= d; i++) pre[i + 1] = pre[i] * (((X - i) % MOD + MOD) % MOD) % MOD;
            suf[d + 1] = 1;
            for (int i = d; i >= 0; i--) suf[i] = suf[i + 1] * (((X - i) % MOD + MOD) % MOD) % MOD;
            fact[0] = 1;
            for (int i = 1; i <= d; i++) fact[i] = fact[i - 1] * i % MOD;
            S = 0;
            for (int i = 0; i <= d; i++) {
                ll num = pre[i] * suf[i + 1] % MOD;
                ll den = fact[i] * fact[d - i] % MOD;
                ll term = T[i] * num % MOD * pw(den, MOD - 2) % MOD;
                if ((d - i) & 1) term = (MOD - term) % MOD;
                S = (S + term) % MOD;
            }
        }

        ll ans = q % MOD * S % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
