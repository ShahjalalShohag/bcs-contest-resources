#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 5 * 1e6 + 5;
const int MOD = 998244353;
 
vector<int> spf(MAX);
vector<vector<int>> prime_to_indices(MAX);
vector<int> active_primes;
 
void compute_spf() {
    for (int i = 0; i < MAX; ++i) {
        spf[i] = i;
    }
    for (int i = 2; i * i < MAX; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}
 
vector<int> get_prime_factors(int x) {
    vector<int> res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) x /= p;
    }
    return res;
}
 
void solve() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
 
    for (int p : active_primes) 
        prime_to_indices[p].clear();
    active_primes.clear();
    vector<vector<int>> pf(n);
 
    for (int i = 0; i < n; ++i) {
        pf[i] = get_prime_factors(a[i]);
        for (int p : pf[i]) {
            if (prime_to_indices[p].empty())
                active_primes.push_back(p);
            prime_to_indices[p].push_back(i);
            if (prime_to_indices[p].size() > 2) {
                cout << 0 << '\n';
                return;
            }
        }
    }
 
    vector<set<int>> adj(n);
    for (int p : active_primes) {
        if (prime_to_indices[p].size() == 2) {
            int u = prime_to_indices[p][0], v = prime_to_indices[p][1];
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }
 
    vector<bool> visited(n, false);
    int bipartite = 0, free = 0;
    int ans = 1;
 
    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;

        int nodes = 0, edges = 0;
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            nodes++;
            edges += adj[u].size();

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        edges /= 2;

        bool is_bipartite = (edges == nodes - 1 || edges == nodes);
 
        if (!is_bipartite) {
            cout << 0 << '\n';
            return;
        }
 
        if (nodes == 1) free++;
        else bipartite++;
 
        ans = 2LL * ans % MOD;
    }
 
    int bad = (bipartite == 0 && free > 0) ? 2 : 0;
    ans = (ans - bad + MOD) % MOD;
    cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    compute_spf();
 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
 
    return 0;
}
