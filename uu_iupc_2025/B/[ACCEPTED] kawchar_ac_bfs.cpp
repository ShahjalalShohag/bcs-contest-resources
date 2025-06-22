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
 
    vector<vector<int>> adj(n);
    for (int p : active_primes) {
        if (prime_to_indices[p].size() == 2) {
            int u = prime_to_indices[p][0], v = prime_to_indices[p][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
 
    vector<int> color(n, -1);
    int bipartite = 0, free = 0;
    int ans = 1;
 
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
 
        int count = 0;
        bool is_bipartite = true;
        queue<int> q;
        q.push(i);
        color[i] = 0;
 
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ++count;
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    is_bipartite = false;
                }
            }
        }
 
        if (!is_bipartite) {
            cout << 0 << '\n';
            return;
        }
 
        if (count == 1) free++;
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
