#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> a(n, 1000000000);
        vector<tuple<int, int, int>> edges;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u; --v;
            edges.emplace_back(u, v, w);
            a[u] = min(a[u], w);
            a[v] = min(a[v], w);
        }

        // After assigning upper bounds, validate constraints
        bool ok = true;
        for (const auto& [u, v, w] : edges) {
            int au = a[u], av = a[v];
            if (max(au, av) != w) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "-1\n";
        } else {
            for (int i = 0; i < n; ++i) {
                cout << a[i] << (i + 1 < n ? ' ' : '\n');
            }
        }
    }

    return 0;
}
