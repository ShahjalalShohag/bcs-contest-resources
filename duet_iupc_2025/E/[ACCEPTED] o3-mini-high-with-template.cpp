#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template for Min‐Cost Max‐Flow
// Works for directed graphs (set directed=true) and handles negative edge costs
// Does not handle negative cycles in the residual graph
// Complexity: O(min(E^2·V·logV, E·logV·flow))
using T = long long;
const T inf = (T)1e18;

struct MCMF {
    struct edge {
        int u, v;
        T cap, cost;
        int id;
        edge(int _u, int _v, T _cap, T _cost, int _id)
          : u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
    };
    int n, s, t, mxid;
    T flow, cost;
    vector<vector<int>> g;
    vector<edge> e;
    vector<T> dist, potential;
    vector<int> par;
    bool hasNegative;

    MCMF(int _n = 0) {
        n = _n;
        g.assign(n, {});
        hasNegative = false;
        mxid = 0;
    }

    void add_edge(int u, int v, T cap, T cost, int id = -1, bool directed = true) {
        if (cost < 0) hasNegative = true;
        g[u].push_back(e.size());
        e.emplace_back(u, v, cap, cost, id);
        g[v].push_back(e.size());
        e.emplace_back(v, u, 0, -cost, -1);
        mxid = max(mxid, id);
        if (!directed) {
            // add the reverse direction too
            add_edge(v, u, cap, cost, -1, true);
        }
    }

    bool dijkstra() {
        dist.assign(n, inf);
        par.assign(n, -1);
        dist[s] = 0;
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [cd, u] = pq.top(); pq.pop();
            if (cd > dist[u]) continue;
            for (int idx : g[u]) {
                auto &ed = e[idx];
                if (ed.cap == 0) continue;
                int v = ed.v;
                T w = ed.cost + potential[u] - potential[v];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    par[v] = idx;
                    pq.push({dist[v], v});
                }
            }
        }
        if (dist[t] == inf) return false;
        // re‐weight potentials
        for (int i = 0; i < n; i++) {
            if (dist[i] < inf) potential[i] += dist[i];
        }
        return true;
    }

    T send_flow(int v, T pushed) {
        if (v == s) return pushed;
        int idx = par[v];
        auto &ed = e[idx];
        T got = send_flow(ed.u, min(pushed, ed.cap));
        ed.cap -= got;
        e[idx^1].cap += got;
        cost += got * ed.cost;
        return got;
    }

    // Send up to 'maxflow' units from s to t, returns {flow_sent, min_cost}
    pair<T,T> solve(int _s, int _t, T maxflow = inf) {
        s = _s; t = _t;
        flow = cost = 0;
        potential.assign(n, 0);

        // If there are negative costs, run Bellman‐Ford once to initialize potentials
        if (hasNegative) {
            vector<T> bf(n, inf);
            bf[s] = 0;
            for (int it = 0; it < n-1; it++) {
                bool any = false;
                for (auto &ed : e) {
                    if (ed.cap > 0 && bf[ed.u] + ed.cost < bf[ed.v]) {
                        bf[ed.v] = bf[ed.u] + ed.cost;
                        any = true;
                    }
                }
                if (!any) break;
            }
            for (int i = 0; i < n; i++) {
                if (bf[i] < inf) potential[i] = bf[i];
            }
        }

        // main MCMF loop
        while (flow < maxflow && dijkstra()) {
            T pushed = send_flow(t, maxflow - flow);
            flow += pushed;
        }
        return {flow, cost};
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n, m, k, d;
        cin >> n >> m >> k >> d;
        vector<ll> c(d+1);
        for (int i = 0; i <= d; i++) {
            cin >> c[i];
        }

        // Precompute convex marginal costs Δ[x] = x·f(x) - (x-1)·f(x-1)
        vector<ll> g(k+1), delta(k+1);
        g[0] = 0;
        for (int x = 1; x <= k; x++){
            __int128 fx = 0, pw = 1;
            for (int i = 0; i <= d; i++){
                if (i > 0) pw *= x;
                fx += (__int128)c[i] * pw;
            }
            __int128 gx = fx * x;
            g[x]       = (ll)gx;
            delta[x]   = g[x] - g[x-1];
        }

        // Build flow network with n nodes (0..n-1)
        MCMF mcmf(n);
        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            --u; --v;
            // replicate this edge k times with unit capacity and increasing cost
            for (int x = 1; x <= k; x++){
                mcmf.add_edge(u, v, 1, delta[x]);
            }
        }

        // Send exactly k units of flow from 0 to n-1
        auto [sent, minCost] = mcmf.solve(0, n-1, k);
        // sent must equal k by problem guarantee
        cout << minCost << "\n";
    }

    return 0;
}
