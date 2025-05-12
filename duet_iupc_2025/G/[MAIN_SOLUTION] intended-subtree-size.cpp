#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;

int sz[MAXN];
int fac[MAXN];

int mod_pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = (1LL * res * a) % mod;
        a = (1LL * a * a) % mod;
        b >>= 1;
    }
    return res;
}

void precompute_factorials(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (1LL * fac[i - 1] * i) % MOD;
    }
}

int count_ways(int n, const vector<int>& parent) {
    for (int i = 0; i < n; ++i) 
        sz[i] = 1;
    for (int i = n-1; i > 0; --i) {
        sz[parent[i]] += sz[i];
    }

    int denom = 1;
    for(int i = 0; i<n; ++i) {
        denom = 1ll * denom * sz[i] % MOD;
    }
    return (1LL * fac[n] * mod_pow(denom, MOD - 2, MOD)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute_factorials(MAXN - 1);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] != -1) a[i]--; 
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            if (b[i] != -1) b[i]--;
        }

        int cnt_a = count_ways(n, a);
        int cnt_b = count_ways(n, b);
        int result = (1LL * cnt_a * mod_pow(cnt_b, MOD - 2, MOD)) % MOD;
        cout << result << "\n";
    }

    return 0;
}
