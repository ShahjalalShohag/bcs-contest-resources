#include <bits/stdc++.h>

using namespace std;
const int mod = 998244353;
const int maxn = 1000005;

vector<int> adj[maxn];
long long ways[maxn];
int sub[maxn];
long long fac[maxn];
long long inv_fac[maxn];
int from[maxn], to[maxn];
long long edge_ways[maxn];

long long modpow(long long base, int exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

long long inverse(long long x) {
    return modpow(x, mod - 2);
}

void mult(long long &a, long long b) {
    a = (a * b) % mod;
}

void divide(long long &a, long long b) {
    a = (a * inverse(b)) % mod;
}

void calc_topsort(int x, int par) {
    ways[x] = 1;
    sub[x]  = 1;
    for(int e : adj[x]) {
        int u = from[e] + to[e] - x;
        if (u != par) {
            calc_topsort(u, x);
            sub[x] += sub[u];
            mult(ways[x], ways[u]);
            divide(ways[x], fac[sub[u]]);
            ways[x] %= mod;
        }
    }
    mult(ways[x], fac[sub[x] - 1]);
}

void reroot(int x, int u) {
    // reroot from x to u
    // change ways[x] and ways[u] such that u is now the root
    // same for sub[x] and sub[u]
    long long u_ways = ways[u];
    long long x_ways = ways[x];

    int u_sub = sub[u];
    int x_sub = sub[x];

    divide(x_ways, ways[u]);
    mult(x_ways, fac[sub[u]]);
    divide(x_ways, fac[sub[x] - 1]);
    mult(x_ways, fac[sub[x] - sub[u] - 1]);

    mult(u_ways, x_ways);
    divide(u_ways, fac[sub[x] - sub[u]]);
    divide(u_ways, fac[sub[u] - 1]);
    mult(u_ways, fac[sub[x] - 1]);

    sub[u] = x_sub;
    sub[x] = x_sub - u_sub;
    ways[x] = x_ways;
    ways[u] = u_ways;
}

void reroot_dfs(int x, int par) {
    for(int e : adj[x]) {
        int u = from[e] ^ to[e] ^ x;
        mult(edge_ways[e], ways[u]);
        divide(edge_ways[e], fac[sub[u] - 1]);
    }
    for(int e : adj[x]) {
        int u = from[e] ^ to[e] ^ x;
        if (u != par) {
            long long before_x = ways[x];
            long long before_u = ways[u];
            int before_sub_x = sub[x];
            int before_sub_u = sub[u];
            reroot(x, u);
            reroot_dfs(u, x);
            // Restore
            ways[x] = before_x;
            ways[u] = before_u;
            sub[x] = before_sub_x;
            sub[u] = before_sub_u;
            // reroot(u, x);
            // assert(ways[x] == before_x);
            // assert(ways[u] == before_u);
        }
    }
}

void solve() {
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
        edge_ways[i] = 1;
    }
    for(int i = 1; i < n; i++) {
        scanf("%d %d", &from[i], &to[i]);
        adj[from[i]].push_back(i);
        adj[to[i]].push_back(i);
    }
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }

    calc_topsort(1, -1);
    reroot_dfs(1, -1);

    // Use hockey stick identity to calculate answer
    // sum of i=1 to k of C(i, n-1) = C(k+1, n)

    long long ans = 1;
    for(int i = 0; i < n; i++) {
        mult(ans, (k + 1 - i));
    }
    mult(ans, inverse(fac[n]));
    long long total = 0;
    for (int i = 1; i < n; i++) {
        total += edge_ways[i];
        total %= mod;
    }
    mult(total, fac[n - 2]);
    mult(ans, total);
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}