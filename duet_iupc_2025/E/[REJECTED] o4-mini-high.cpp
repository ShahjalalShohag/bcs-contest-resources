#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n, m, k, d;
        cin >> n >> m >> k >> d;
        vector<ll> c(d+1);
        for (int i = 0; i <= d; i++) 
            cin >> c[i];

        // read graph
        vector<pair<int,int>> edges(m);
        vector<vector<pair<int,int>>> adj(n+1);
        for (int e = 0; e < m; e++){
            int u, v;
            cin >> u >> v;
            edges[e] = {u, v};
            adj[u].emplace_back(v, e);
        }

        // Precompute g[x] = x * f(x)  and  marginal[x] = g[x] - g[x-1]
        vector<ll> g(k+1), marginal(k+1);
        g[0] = 0;
        for (int x = 1; x <= k; x++){
            __int128 fx = 0, pw = 1;
            for (int i = 0; i <= d; i++){
                if (i == 0) pw = 1;
                else        pw *= x;
                fx += (__int128)c[i] * pw;
            }
            __int128 gx = fx * x;
            g[x] = (ll)gx;
            marginal[x] = (ll)(gx - g[x-1]);
        }

        // usage count per edge
        vector<int> usage(m, 0);
        ll total_cost = 0;

        // reusable arrays for Dijkstra
        const ll INF = LLONG_MAX/4;
        vector<ll> dist(n+1);
        vector<int> prev_node(n+1), prev_edge(n+1);

        // repeat k times, each time send one unit along the current shortest path
        for (int it = 0; it < k; it++){
            // initialize
            fill(dist.begin(), dist.end(), INF);
            dist[1] = 0;
            fill(prev_node.begin(), prev_node.end(), -1);
            fill(prev_edge.begin(), prev_edge.end(), -1);

            // Dijkstra
            using pli = pair<ll,int>;
            priority_queue<pli, vector<pli>, greater<pli>> pq;
            pq.push({0, 1});
            while (!pq.empty()){
                auto [cd, u] = pq.top(); pq.pop();
                if (cd > dist[u]) continue;
                if (u == n) break;  // we found the best distance to n
                for (auto &pr : adj[u]){
                    int v = pr.first, e = pr.second;
                    ll w = marginal[ usage[e] + 1 ];
                    if (dist[v] > cd + w){
                        dist[v] = cd + w;
                        prev_node[v] = u;
                        prev_edge[v] = e;
                        pq.push({dist[v], v});
                    }
                }
            }

            // add to total cost
            total_cost += dist[n];

            // walk back the path, increment usage
            int v = n;
            while (v != 1){
                int e = prev_edge[v];
                usage[e]++;
                v = prev_node[v];
            }
        }

        cout << total_cost << "\n";
    }
    return 0;
}
