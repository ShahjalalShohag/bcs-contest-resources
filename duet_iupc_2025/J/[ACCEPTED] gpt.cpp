#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
const int MAXN = 300000;

int add(int a, int b) { a += b; if (a >= MOD) a -= MOD; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += MOD; return a; }
int mul(ll a, ll b) { return int(a * b % MOD); }
int modexp(int a, ll e = MOD - 2) {
    int r = 1;
    while (e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

int fact[MAXN+1], invfact[MAXN+1], spf[MAXN+1], cntPr[MAXN+1];

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fact[n], mul(invfact[k], invfact[n - k]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials and inverse factorials
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i)
        fact[i] = mul(fact[i - 1], i);
    invfact[MAXN] = modexp(fact[MAXN]);
    for (int i = MAXN; i > 0; --i)
        invfact[i - 1] = mul(invfact[i], i);

    // Sieve for smallest prime factor (SPF)
    for (int i = 2; i <= MAXN; ++i) {
        if (spf[i] == 0) {
            for (int j = i; j <= MAXN; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }

    int T;
    cin >> T;
    vector<int> usedPrimes;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];

        usedPrimes.clear();
        // Count how many a[i] are divisible by each prime
        for (int x : a) {
            int v = x, last = 0;
            while (v > 1) {
                int p = spf[v];
                if (p != last) {
                    if (cntPr[p]++ == 0)
                        usedPrimes.push_back(p);
                    last = p;
                }
                while (v % p == 0) v /= p;
            }
        }

        int totalSubs = C(n, k);
        int answer = 0;

        // For each prime p, add p * (#subsequences where p | lcm)
        for (int p : usedPrimes) {
            int c = cntPr[p];
            int withoutP = C(n - c, k);
            int withP = sub(totalSubs, withoutP);
            answer = add(answer, mul(withP, p));
            cntPr[p] = 0;  // reset for next test
        }

        cout << answer << "\n";
    }
    return 0;
}
