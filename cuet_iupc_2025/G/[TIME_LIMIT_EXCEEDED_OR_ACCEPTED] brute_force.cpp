#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define all(x) x.begin(),x.end()
#define Max 10000000000000000

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

// Lowest common ancestor (LCA) using Binary Lifting
class LCA {
public:
    int LOG;
    vector<vector<int>> up;
    vector<int> depth;
    LCA(int n, int root, const vector<vector<int>>& adj) {
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        up.assign(n + 1, vector<int>(LOG));
        depth.assign(n + 1, 0);
        function<void(int, int)> dfs = [&](int u, int p) {
            up[u][0] = p;
            for (int i = 1; i < LOG; i++) {
                up[u][i] = up[up[u][i - 1]][i - 1];
            }
            for (int v : adj[u]) {
                if (v != p) {
                    depth[v] = depth[u] + 1;
                    dfs(v, u);
                }
            }
        };
        dfs(root, root);
    }
    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
};

int main()
{

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        LCA lca = LCA(n, 1, adj);
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }

        vector<ll> ans(n, 0);
        ans[0] = ((ll)n * (ll)(n + 1)) / 2LL;
        int idx = 1;

        while(p.size() != 1) {
            vector<int> f;
            ll sum = 0;
            for(int i = 1; i < p.size(); i++) {
                int curr_lca = lca.get_lca(p[i], p[i - 1]);
                f.push_back(curr_lca);
                sum += (ll)curr_lca;
            }
            ans[idx] = sum;
            idx++;
            p = f;
        }

        for(int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    

    return 0;
}