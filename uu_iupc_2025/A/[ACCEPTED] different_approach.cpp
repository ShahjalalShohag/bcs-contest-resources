#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        edges.push_back({w, {u, v}});
    }

    vector<int> ans(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        if (!adj[i].empty()) {
            ans[i] = adj[i][0].first;
        }
        else {
            ans[i] = 1;
        }
    }

    for (auto edge: edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (max(ans[u], ans[v]) != w) {
            cout << "-1\n";
            return;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

}