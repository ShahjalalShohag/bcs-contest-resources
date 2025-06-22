// Naive Set-Rebuild TLE Solution
// Maintain a set of unsatisfied edges; each round, pick the smallest-weight unsatisfied edge by scanning the set,
// assign its endpoints, then completely rebuild the set by checking all edges again.
// Worst-case: O(n * (m + m)) = O(n*m), which TLEs when n,m ~ 3e5.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int u, v; ll w; };

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

        vector<ll> a(n + 1, 1);
        set<int> unsat;
        for (int i = 0; i < m; i++) unsat.insert(i);

        // Greedy rounds until no unsatisfied edges or break
        while (!unsat.empty()) {
            // Find minimum-weight edge among unsatisfied (O(m) scan)
            ll bestW = LLONG_MAX;
            int bestIdx = -1;
            for (int idx : unsat) {
                if (edges[idx].w < bestW) {
                    bestW = edges[idx].w;
                    bestIdx = idx;
                }
            }
            if (bestIdx == -1) break;

            // Assign endpoints to satisfy the chosen edge
            a[edges[bestIdx].u] = bestW;
            a[edges[bestIdx].v] = bestW;

            // Rebuild unsatisfied edges set by checking all edges again (O(m log m))
            unsat.clear();
            for (int i = 0; i < m; i++) {
                if (max(a[edges[i].u], a[edges[i].v]) < edges[i].w) {
                    unsat.insert(i);
                }
            }
        }

        // Final verification
        bool ok = true;
        for (auto &e : edges) {
            if (max(a[e.u], a[e.v]) != e.w) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << -1 << '\n';
        } else {
            for (int i = 1; i <= n; i++) {
                cout << a[i] << (i < n ? ' ' : '\n');
            }
        }
    }
    return 0;
}
