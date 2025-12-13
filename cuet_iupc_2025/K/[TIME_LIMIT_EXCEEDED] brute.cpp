#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
int n, k;
vector<pair<int,int>> adj[N]; // adj[u] = {v, edge_index}
int w[N]; // w[i] = weight of edge i

// Check if a valid removal order exists for current weight assignment
bool canRemove() {
    vector<int> initSums(n + 1);
    for (int u = 1; u <= n; u++) {
        initSums[u] = 0;
        for (auto [v, e] : adj[u]) {
            initSums[u] += w[e];
        }
    }
    
    // Try all permutations of removal order
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    
    do {
        vector<int> sums = initSums;
        vector<bool> removed(n + 1, false);
        int lastSum = INT_MAX;
        bool valid = true;
        
        for (int i = 0; i < n && valid; i++) {
            int u = order[i];
            if (sums[u] >= lastSum) {
                valid = false;
                break;
            }
            lastSum = sums[u];
            removed[u] = true;
            
            // Update neighbors
            for (auto [v, e] : adj[u]) {
                if (!removed[v]) {
                    sums[v] -= w[e];
                }
            }
        }
        
        if (valid) return true;
    } while (next_permutation(order.begin(), order.end()));
    
    return false;
}

int f(int m) {
    // Count valid assignments with weights in [1, m]
    int edges = n - 1;

    int count = 0;
    
    // Enumerate all weight assignments
    function<void(int)> go = [&](int e) {
        if (e == edges) {
            if (canRemove()) count++;
            return;
        }
        for (int wt = 1; wt <= m; wt++) {
            w[e] = wt;
            go(e + 1);
        }
    };
    go(0);
    return count;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) adj[i].clear();
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    
    long long ans = 0;
    for (int m = 1; m <= k; m++) {
        ans = (ans + f(m)) % mod;
    }
    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
