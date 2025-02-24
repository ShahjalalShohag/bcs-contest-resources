#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
using ll = long long int;

struct DSU {
    vector<int> master;
    vector<ll> best;
    DSU(int n, vector<ll> &power): master(n+1), best(power) {
        for(int i = 1; i<=n; i++) {
            master[i] = i;
        }
    }

    int getMaster(int u) {
        if (master[u] == u) return u;
        return master[u] = getMaster(master[u]);
    }

    ll unite(int u, int v, ll p) {
        u = getMaster(u);
        v = getMaster(v);
        master[v] = u;
        best[u] = max({best[u], p, p + best[v]});
        return best[u];
    }

    ll getVal(int u) {
        return best[getMaster(u)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin>>tc;
    for(int cs = 1; cs <= tc; cs++){
        int n;
        cin >> n;
        vector<vector<int>> graph(n+1);
        vector<int> rank(n+1), par(n+1);
        vector<ll> power(n+1), ans(n+1);
        

        for(int i = 2; i<=n; i++){
            int p;
            cin>>p;
            par[i] = p;
            graph[i].push_back(p);
            graph[p].push_back(i);
        }

        for(int i = 1; i<=n; i++){
            cin >> power[i];
        }

        for(int i = 1; i<=n; i++){
            cin >> rank[i];
        }

        auto powerPref = power;

        auto dfs = [&](auto& self, int u, int p) -> void {
            for (int v : graph[u]) {
                if (v == p) continue;
                powerPref[v] += powerPref[u];
                self(self, v, u);
            }
        };
        dfs(dfs, 1, -1);

        DSU dsu(n, power);

        vector<int> sorted(n);
        iota(sorted.begin(), sorted.end(), 1);
        sort(sorted.begin(), sorted.end(), [&](int i, int j) {
            return rank[i] < rank[j];
        });

        for(auto u: sorted) {
            ans[u] = power[u];
            ll prv = power[u];
            for(auto v : graph[u]) {
                if (rank[v] > rank[u]) continue;
                
                if (par[u] == v) {
                    continue;
                }
                
                ll nxt = dsu.getVal(v);
                ans[u] = max(ans[u], prv + nxt);
                prv = dsu.unite(u, v, power[u]);
            }

            if (u != 1 && rank[par[u]] < rank[u]) {
                int v = par[u];
                auto vMaster = dsu.getMaster(v);
                int x = dsu.unite(v, u, powerPref[u] - powerPref[vMaster] + power[vMaster] - power[u]);
            }
        }

        for(int i = 1; i<=n; i++){
            cout << ans[i] << ' ';
        }
        cout<< '\n'; 
    }

    return 0;
}