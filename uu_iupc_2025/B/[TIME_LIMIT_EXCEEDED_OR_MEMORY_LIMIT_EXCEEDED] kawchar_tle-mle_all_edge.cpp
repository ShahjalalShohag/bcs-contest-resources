#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX = 5'000'005;
const int MOD = 998244353;

int spf[MAX];

void compute_spf() {
    for (int i = 1; i < MAX; ++i) {
        spf[i] = i;
    }
    for (int i = 2; i * i < MAX; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<int> get_prime_factors(int x) {
    vector<int> factors;
    while (x > 1) {
        int p = spf[x];
        factors.push_back(p);
        while (x % p == 0) {
            x /= p;
        }
    }
    return factors;
}

ll mod_pow(ll base, ll exp, ll mod = MOD) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

struct UnionFind {
    vector<int> parent, rnk;
    int components;
    
    UnionFind(int n)
        : parent(n), rnk(n, 0), components(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rnk[x] < rnk[y]) swap(x, y);
        parent[y] = x;
        if (rnk[x] == rnk[y]) ++rnk[x];
        --components;
        return true;
    }
};

bool dfs_bipartite(int u, const vector<vector<int>>& adj, vector<int>& color, int c) {
    color[u] = c;
    for (int v : adj[u]) {
        if (color[v] == -1) {
            if (!dfs_bipartite(v, adj, color, 1 - c)) return false;
        } else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) {
        cin >> x;
    }
    
    UnionFind uf(n);
    map<int, vector<int>> prime_to_items;
    for (int i = 0; i < n; ++i) {
        for (int p : get_prime_factors(a[i])) {
            prime_to_items[p].push_back(i);
        }
    }
    for (auto& [p, items] : prime_to_items) {
        for (int i = 1; i < (int)items.size(); ++i) {
            uf.unite(items[0], items[i]);
        }
    }
    
    map<int, vector<int>> comps;
    for (int i = 0; i < n; ++i) {
        comps[uf.find(i)].push_back(i);
    }
    
    bool valid = true;
    int valid_components = 0;
    bool has_edges = false;
    
    for (auto& [root, items] : comps) {
        int sz = items.size();
        if (sz == 1) {
            ++valid_components;
            continue;
        }
        has_edges = true;
        
        vector<vector<int>> adj(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                if (gcd(a[items[i]], a[items[j]]) > 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        vector<int> color(sz, -1);
        int sub_components = 0;
        for (int i = 0; i < sz; ++i) {
            if (color[i] == -1) {
                if (!dfs_bipartite(i, adj, color, 0)) {
                    valid = false;
                    break;
                }
                ++sub_components;
            }
        }
        if (!valid) break;
        valid_components += sub_components;
    }
    
    if (!valid) {
        cout << 0 << "\n";
    } else {
        ll ans = mod_pow(2, valid_components);
        if (!has_edges) {
            ans = (ans - 2 + MOD) % MOD;
        }
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    compute_spf();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
