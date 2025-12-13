#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
int n, k;
vector<pair<int,int>> adj[N]; // adj[u] = {v, edge_index}
int w[N]; // w[i] = weight of edge i

// Check if a valid removal order exists for current weight assignment
// Greedy: always remove the leaf with highest incident edge weight
bool canRemove() {
    vector<int> sums(n + 1);
    vector<int> deg(n + 1);
    for (int u = 1; u <= n; u++) {
        sums[u] = 0;
        deg[u] = adj[u].size();
        for (auto [v, e] : adj[u]) {
            sums[u] += w[e];
        }
    }
    
    vector<bool> removed(n + 1, false);
    int lastSum = INT_MAX;
    
    for (int step = 0; step < n; step++) {
        // Find leaf (deg <= 1) with maximum sum
        int best = -1, bestSum = -1;
        for (int u = 1; u <= n; u++) {
            if (!removed[u] && deg[u] <= 1 && sums[u] > bestSum) {
                bestSum = sums[u];
                best = u;
            }
        }
        
        if (best == -1) return false; // no leaf found (shouldn't happen in a tree)
        if (bestSum >= lastSum) return false; // not strictly decreasing
        
        lastSum = bestSum;
        removed[best] = true;
        
        // Update neighbors
        for (auto [v, e] : adj[best]) {
            if (!removed[v]) {
                sums[v] -= w[e];
                deg[v]--;
            }
        }
    }
    return true;
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
