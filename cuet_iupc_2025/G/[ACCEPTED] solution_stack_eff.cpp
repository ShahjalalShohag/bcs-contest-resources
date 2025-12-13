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
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        LCA lca = LCA(n, 1, adj);

        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &p[i]);
        }

        vector<ll> ans(n + 1, 0);
        ans[0] = ((ll)n * (ll)(n + 1)) / 2LL;

        vector<ll> f;
        for (int i = 1; i < n; i++) {
            int curr_lca = lca.get_lca(p[i], p[i + 1]);
            f.push_back(curr_lca);
        }

        if(n == 2) {
            printf("%lld 1\n", ans[0]);
            continue;
        }
        
        int l[n], r[n];
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));

        stack<int> ls, rs;
        for(int i = 0; i < f.size(); i++) {
            while(!ls.empty() && lca.depth[f[ls.top()]] > lca.depth[f[i]]) {
                ls.pop();
            }
            if(ls.empty()) l[i] = i + 1;
            else l[i] = i - ls.top();
            ls.push(i);
        }

        for(int i = f.size() - 1; i >= 0; i--) {
            while(!rs.empty() && lca.depth[f[rs.top()]] > lca.depth[f[i]]) {
                rs.pop();
            }
            if(rs.empty()) r[i] = n - i - 1;
            else r[i] = rs.top() - i;
            rs.push(i);
        }

        for(int i = n - 1; i >= 0; i--) {
            if(i + r[i] < n - 1 && lca.depth[f[i]] == lca.depth[f[i + r[i]]]) {
                r[i] += r[i + r[i]];
            }
        }

        ll mark[4][n + 2];
        memset(mark, 0, sizeof(mark));

        for(int i = 0; i < f.size(); i++) {
            int left_idx = 1, right_idx = l[i] + r[i] - 1;
            int min_seg = min(l[i], r[i]);
            int max_seg = max(l[i], r[i]);
            mark[0][left_idx] += f[i];
            mark[1][min_seg + 1] += f[i];
            mark[2][max_seg + 1] += f[i];
            mark[3][right_idx + 2] += f[i];
        }

        ll tmp = 0;
        for(int i = 1; i < n; i++) {
            tmp += mark[0][i];
            tmp -= mark[1][i];
            tmp -= mark[2][i];
            tmp += mark[3][i];

            if(i > 1) ans[i] = ans[i - 1] + tmp;
            else ans[i] = tmp;
        }
        for(int i = 0; i < n; i++) {
            printf("%lld ", ans[i]);
        }
        printf("\n");
    }
    

    return 0;
}