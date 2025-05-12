#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = LLONG_MAX/4;

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

        // read edges
        vector<vector<pair<int,int>>> adj(n+1);
        for (int e = 0; e < m; e++){
            int u,v;
            cin >> u >> v;
            adj[u].emplace_back(v, e);
        }

        // 1) Precompute g[x] = x*f(x) and marginals Δ[x]
        vector<ll> g(k+1), delta(k+1);
        g[0] = 0;
        for (int x = 1; x <= k; x++){
            __int128 fx = 0, pw = 1;
            // compute f(x)
            for (int i = 0; i <= d; i++){
                if (i>0) pw *= x;
                fx += (__int128)c[i] * pw;
            }
            __int128 gx = fx * x; 
            g[x]     = (ll)gx;
            delta[x] = (ll)(gx - g[x-1]);
        }

        // usage count per edge
        vector<int> used(m, 0);
        ll totalCost = 0;

        // helper arrays for Dijkstra
        vector<ll> dist(n+1);
        vector<int> parentEdge(n+1), parentNode(n+1);

        // 2) Repeat greedy augmentation k times
        for (int it = 0; it < k; it++){
            // init distances
            fill(dist.begin(), dist.end(), INF);
            dist[1] = 0;
            fill(parentEdge.begin(), parentEdge.end(), -1);
            fill(parentNode.begin(), parentNode.end(), -1);

            // Dijkstra from 1
            priority_queue<pair<ll,int>,
                           vector<pair<ll,int>>,
                           greater<>> pq;
            pq.push({0,1});
            while(!pq.empty()){
                auto [cd,u] = pq.top(); 
                pq.pop();
                if (cd > dist[u]) continue;
                if (u == n) break;  // we can stop once we settle n
                for (auto &pe : adj[u]){
                    int v = pe.first, e = pe.second;
                    ll w = delta[ used[e] + 1 ];
                    if (dist[v] > cd + w){
                        dist[v] = cd + w;
                        parentNode[v] = u;
                        parentEdge[v] = e;
                        pq.push({dist[v], v});
                    }
                }
            }

            // add this path's cost
            totalCost += dist[n];

            // walk back to increment usages
            for (int v = n; v != 1; v = parentNode[v]){
                int e = parentEdge[v];
                used[e]++;
            }
        }

        cout << totalCost << "\n";
    }
    return 0;
}
