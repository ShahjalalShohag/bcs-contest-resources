// "Improved" Greedy (Still Wrong) - sorts edges and assigns in ascending order
// This seems correct but fails on specific cycles where later larger weights cannot override earlier assignments.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        // Sort edges by weight ascending
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });

        vector<ll> a(n + 1, -1);
        // Greedy assignment
        for (auto &e : edges) {
            int u = e.u, v = e.v;
            ll w = e.w;
            if (a[u] == -1 && a[v] == -1) {
                // Both unassigned: give both the edge weight
                a[u] = w;
                a[v] = w;
            } else if (a[u] == -1) {
                // Assign u so max(a_u, a_v) == w
                a[u] = w;
            } else if (a[v] == -1) {
                a[v] = w;
            }
            // If both assigned, skip - might violate later
        }
        // Fill any leftover vertices with 1
        for (int i = 1; i <= n; i++) {
            if (a[i] == -1) a[i] = 1;
        }

        // Output (may violate max(a_u,a_v)=w in tricky cases)
        for (int i = 1; i <= n; i++) {
            cout << a[i] << (i < n ? ' ' : '\n');
        }
    }
    return 0;
}
