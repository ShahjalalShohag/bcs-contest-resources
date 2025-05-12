#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
 
struct Edge {
    int to, rev;
    ll cap, cost;
};
 
class MinCostMaxFlow {
    int n;
    vector<vector<Edge>> g;
    vector<ll> dist, pot;
    vector<int> prevv, preve;
 
public:
    MinCostMaxFlow(int n) : n(n), g(n), dist(n), pot(n), prevv(n), preve(n) {}
 
    void add_edge(int from, int to, ll cap, ll cost) {
        g[from].push_back({to, (int)g[to].size(), cap, cost});
        g[to].push_back({from, (int)g[from].size() - 1, 0, -cost});
    }
 
    pair<ll, ll> flow(int s, int t, ll maxf) {
        ll flow = 0, cost = 0;
        fill(pot.begin(), pot.end(), 0);
 
        while (flow < maxf) {
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            pq.emplace(0, s);
 
            while (!pq.empty()) {
                auto [d, v] = pq.top(); pq.pop();
                if (dist[v] < d) continue;
                for (int i = 0; i < g[v].size(); ++i) {
                    Edge &e = g[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + pot[v] - pot[e.to]) {
                        dist[e.to] = dist[v] + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.emplace(dist[e.to], e.to);
                    }
                }
            }
 
            if (dist[t] == INF) break;
 
            for (int v = 0; v < n; ++v) pot[v] += dist[v];
 
            ll addf = maxf - flow;
            for (int v = t; v != s; v = prevv[v])
                addf = min(addf, g[prevv[v]][preve[v]].cap);
 
            flow += addf;
            cost += addf * pot[t];
            for (int v = t; v != s; v = prevv[v]) {
                Edge &e = g[prevv[v]][preve[v]];
                e.cap -= addf;
                g[v][e.rev].cap += addf;
            }
        }
        return {flow, cost};
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int t; cin >> t;
    while (t--) {
        int n, m, k, d;
        cin >> n >> m >> k >> d;
 
        vector<int> c(d + 1);
        for (int i = 0; i <= d; ++i) cin >> c[i];
 
        auto f = [&](int x) {
            ll res = 0, xp = 1;
            for (int i = 0; i <= d; ++i) {
                res += 1LL * c[i] * xp;
                xp *= x;
            }
            return res;
        };
 
        MinCostMaxFlow mcmf(n + 1);
 
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            for (int j = 1; j <= min(k, 49); ++j) {
                ll cost = j * f(j) - (j - 1) * f(j - 1);
                mcmf.add_edge(u, v, 1, cost);
            }
        }
 
        auto [flow, cost] = mcmf.flow(1, n, k);
        if (flow < k) assert("oh no");
        else cout << cost << '\n';
    }
 
    return 0;
}
