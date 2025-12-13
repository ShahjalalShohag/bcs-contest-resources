#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
using ll = long long;

vector<int> g[N];
int sz[N], inv[N];
int n;

int power(int n, long long k) {
    int ans = 1 % mod;
    while (k) {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}

void prec() {
    for (int i = 1; i < N; i++) {
        inv[i] = power(i, mod - 2);
    }
}

// Compute product of 1/sz[v] for all v != root when rooted at 'root'
// O(n) per root
int compute_for_root(int root) {
    // BFS/DFS to compute subtree sizes when rooted at 'root'
    vector<int> parent(n + 1, 0);
    vector<int> subtree(n + 1, 1);
    vector<int> order;
    
    queue<int> q;
    q.push(root);
    parent[root] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (parent[u] != v) {
                parent[v] = u;
                q.push(v);
            }
        }
    }
    
    // Compute subtree sizes in reverse BFS order
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (parent[u] != -1) {
            subtree[parent[u]] += subtree[u];
        }
    }
    
    // Product of 1/sz[v] for all v != root
    int prod = 1;
    for (int v = 1; v <= n; v++) {
        if (v != root) {
            prod = 1LL * prod * inv[subtree[v]] % mod;
        }
    }
    
    return prod;
}

void solve() {
    int k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (k < n - 1) {
        cout << 0 << '\n';
        return;
    }

    // Sum over all roots
    int tot_inv_prod = 0;
    for (int root = 1; root <= n; root++) {
        tot_inv_prod = (tot_inv_prod + compute_for_root(root)) % mod;
    }

    // C(k + 1, n) = (k+1) * k * ... * (k+1 - n + 1)
    int ways = 1;
    for (int i = 0; i < n; i++) {
        ways = 1LL * ways * ((k + 1 - i) % mod + mod) % mod;
    }

    int ans = 1LL * tot_inv_prod * ways % mod;
    ans = 1LL * ans * inv[n] % mod;
    ans = 1LL * ans * inv[2] % mod;

    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
