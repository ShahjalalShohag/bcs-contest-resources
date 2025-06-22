#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n, m; cin >> n >> m;

    vector<deque<pair<int, int>>> adj(n + 1);
    vector<pair<int, pair<int, int>>> edges;

    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        edges.push_back({w, {u, v}});
    }

    sort(edges.begin(), edges.end());

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<int> maxLimit(n + 1, INT_MAX);
    vector<int> fixedValue(n + 1, -1);

    for (auto edge: edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (fixedValue[u] == -1 and fixedValue[v] == -1) {
            fixedValue[u] = w;
            fixedValue[v] = w;
            if (maxLimit[u] < w or maxLimit[v] < w) {
                cout << "-1\n";
                return;
            }
            maxLimit[u] = w;
            maxLimit[v] = w;
        }
        else if (fixedValue[u] == -1) {
            fixedValue[u] = w;
            if (maxLimit[u] < w) {
                cout << "-1\n";
                return;
            }
            maxLimit[u] = w;
        }
        else if (fixedValue[v] == -1) {
            fixedValue[v] = w;
            if (maxLimit[v] < w) {
                cout << "-1\n";
                return;
            }
            maxLimit[v] = w;
        }
        else {
            if (fixedValue[u] != w and fixedValue[v] != w) {
                cout << "-1\n";
                return;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (fixedValue[i] == -1) fixedValue[i] = 1;
        cout << fixedValue[i] << " ";
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