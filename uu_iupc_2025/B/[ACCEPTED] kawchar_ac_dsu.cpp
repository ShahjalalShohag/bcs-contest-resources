#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 5 * 1e6 + 5;
const int MOD = 998244353;
 
vector<int> spf(MAX);
vector<vector<int>> prime_to_indices(MAX);
vector<int> active_primes;
 
void compute_spf() {
    for (int i = 0; i < MAX; ++i)
        spf[i] = i;
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
 
pair<int, int> find(int x, vector<int>& parent, vector<int>& parity) {
    if (parent[x] == x) return {x, 0};
    auto [px, pc] = find(parent[x], parent, parity);
    parent[x] = px;
    parity[x] ^= pc;
    return {parent[x], parity[x]};
}
 
bool unite(int u, int v, vector<int>& parent, vector<int>& parity) {
    auto [pu, cu] = find(u, parent, parity);
    auto [pv, cv] = find(v, parent, parity);
    if (pu == pv) return cu != cv;
    parent[pu] = pv;
    parity[pu] = cu ^ cv ^ 1;
    return true;
}
 
int mod_pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}
 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
 
    vector<vector<int>> pf(n);
    for (int p : active_primes) prime_to_indices[p].clear();
    active_primes.clear();
 
    for (int i = 0; i < n; ++i) {
        pf[i] = get_prime_factors(a[i]);
        for (int p : pf[i]) {
            if (prime_to_indices[p].empty()) active_primes.push_back(p);
            prime_to_indices[p].push_back(i);
            if (prime_to_indices[p].size() > 2) {
                cout << 0 << '\n';
                return;
            }
        }
    }
 
    vector<int> parent(n), parity(n), has_edge(n, 0);
    iota(parent.begin(), parent.end(), 0);
    fill(parity.begin(), parity.end(), 0);
 
    for (int p : active_primes) {
        if (prime_to_indices[p].size() == 2) {
            int u = prime_to_indices[p][0], v = prime_to_indices[p][1];
            has_edge[u] = has_edge[v] = 1;
            if (!unite(u, v, parent, parity)) {
                cout << 0 << '\n';
                return;
            }
        }
    }
 
    unordered_map<int, pair<int, bool>> comp_data; // root -> {count, has_edge}
    for (int i = 0; i < n; ++i) {
        auto [r, _] = find(i, parent, parity);
        comp_data[r].first++;
        comp_data[r].second |= has_edge[i];
    }
 
    int bipartite = 0, free = 0;
    for (auto& [_, info] : comp_data) {
        if (info.second) bipartite++;
        else free++;
    }
 
    int ans = mod_pow(2, bipartite + free, MOD);
    if (bipartite == 0 && free > 0) {
        ans = (ans - 2 + MOD) % MOD;
    }
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
