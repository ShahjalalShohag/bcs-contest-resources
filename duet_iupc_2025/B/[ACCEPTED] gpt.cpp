#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 5;

vector<int> tree[MAXN];
int a[MAXN];
int res;

int dfs(int node, int parent) {
    int count = a[node];  // 1 if node is initially 1

    for (int child : tree[node]) {
        if (child == parent) continue;
        int subCount = dfs(child, node);
        if (subCount % 2 == 1) {
            res++;  // need to flip edge (node, child)
        }
        count += subCount;
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // Clear previous test case data
        for (int i = 1; i <= n; i++) {
            tree[i].clear();
        }

        int totalOnes = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            totalOnes += a[i];
        }

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        if (totalOnes % 2 != 0) {
            cout << -1 << "\n";
        } else {
            res = 0;
            dfs(1, -1);  // Root at node 1
            cout << res << "\n";
        }
    }

    return 0;
}
