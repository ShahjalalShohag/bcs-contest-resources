#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;

int sz[MAXN];
int fac[MAXN];
vector<int> tree[MAXN];

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

int ncr(int n, int r) {
    return 1ll * fac[n] * mod_pow(1ll * fac[r] * fac[n-r] % MOD, MOD-2, MOD) % MOD;
}

void dfs1(int u) {
    sz[u] = 1;
    for(int v : tree[u]) {
        dfs1(v);
        sz[u] += sz[v];
    }
}

int dfs2(int u) {
    int res = 1;
    int n = sz[u] - 1;
    for(int v : tree[u]) {
        int tmp = dfs2(v);
        res = 1ll * res * ncr(n, sz[v]) % MOD * tmp % MOD;
        n -= sz[v];
    }

    return res;
}

int count_ways(int n, const vector<int>& parent) {
    for(int i = 0; i < n; i++) tree[i].clear();

    for(int i = 1; i < n; i++){
        tree[parent[i]].push_back(i);
    }

    dfs1(0);
    return dfs2(0);
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
