#include <bits/stdc++.h>
using namespace std;

// Same maximal-matching DP, but combines each node's children with prefix/suffix products (no division).

const long long MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> par(n + 1, 0), order;
        order.reserve(n);
        vector<char> vis(n + 1, 0);
        order.push_back(1);
        vis[1] = 1;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int w : adj[u]) if (!vis[w]) { vis[w] = 1; par[w] = u; order.push_back(w); }
        }
        vector<vector<int>> ch(n + 1);
        for (int v : order) if (par[v]) ch[par[v]].push_back(v);

        vector<long long> M(n + 1), P(n + 1), U(n + 1);
        long long ans = 0;
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int v = order[i];
            auto& kids = ch[v];
            int k = (int)kids.size();
            long long prodM = 1, prodS = 1;
            vector<long long> S(k);
            for (int j = 0; j < k; j++) {
                int c = kids[j];
                S[j] = (M[c] + U[c]) % MOD;
                prodM = prodM * M[c] % MOD;
                prodS = prodS * S[j] % MOD;
            }
            vector<long long> pre(k + 1), suf(k + 1);
            pre[0] = 1;
            for (int j = 0; j < k; j++) pre[j + 1] = pre[j] * S[j] % MOD;
            suf[k] = 1;
            for (int j = k - 1; j >= 0; j--) suf[j] = suf[j + 1] * S[j] % MOD;
            long long m = 0;
            for (int j = 0; j < k; j++) m = (m + P[kids[j]] * (pre[j] * suf[j + 1] % MOD)) % MOD;
            M[v] = m;
            P[v] = prodS;
            U[v] = prodM;
            if (par[v] == 0) ans = (M[v] + U[v]) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}
