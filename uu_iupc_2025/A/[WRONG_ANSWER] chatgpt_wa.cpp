#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void solve() {
    int t;
    cin >> t; // Read the number of test cases

    while (t--) {
        int n, m;
        cin >> n >> m; // Read number of vertices and edges

        vector<tuple<int, int, int>> edges; // To store (weight, u, v)
        
        // Read the edges
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back(make_tuple(w, u - 1, v - 1)); // 0-based index
        }

        // Sort edges in descending order based on weight
        sort(edges.rbegin(), edges.rend());

        vector<int> a(n, 0); // Initialize the array a with 0
        
        // Process the edges
        for (const auto& edge : edges) {
            int w, u, v;
            tie(w, u, v) = edge;
            
            if (max(a[u], a[v]) < w) {
                // Set the values of a[u] and a[v] to w if they are less than w
                if (a[u] < w) {
                    a[u] = w;
                }
                if (a[v] < w) {
                    a[v] = w;
                }
            }
        }

        // Validate if the array a satisfies all edges
        bool valid = true;
        for (const auto& edge : edges) {
            int w, u, v;
            tie(w, u, v) = edge;
            if (max(a[u], a[v]) != w) {
                valid = false;
                break;
            }
        }

        // Output the result
        if (valid) {
            for (int i = 0; i < n; ++i) {
                cout << a[i] << " ";
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // For faster I/O
    cin.tie(nullptr);

    solve();
    return 0;
}
