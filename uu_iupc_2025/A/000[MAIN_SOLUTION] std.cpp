#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });

    vector<int> a(n + 1, -1);
    bool possible = true;

    for (const auto& edge : edges) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int w = get<2>(edge);

        if (a[u] == -1 && a[v] == -1) {
            a[u] = w;
            a[v] = w;
        } else if (a[u] == -1) {
            if (a[v] > w) {
                possible = false;
                break;
            }
            a[u] = w;
        } else if (a[v] == -1) {
            if (a[u] > w) {
                possible = false;
                break;
            }
            a[v] = w;
        } else {
            if (max(a[u], a[v]) != w) {
                possible = false;
                break;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) {
            a[i] = 1;
        }
        if (a[i] < 1 || a[i] > 1000000000) {
            possible = false;
        }
    }

    if (possible) {
        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            if (max(a[u], a[v]) != w) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << '\n';
    } else {
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << (i < n ? ' ' : '\n');
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}