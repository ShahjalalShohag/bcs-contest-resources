// Greedy WA Solution - Connect only adjacent indices per prime (chains instead of cliques)
// This will pass most cases but miss triangles (p-group of size >=3) and output >0 when it should be 0.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 5000005;
const int MOD = 998244353;

int lpf[MAXA];

ll modexp(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute least prime factors
    for (int i = 2; i < MAXA; i++) {
        if (!lpf[i]) {
            for (int j = i; j < MAXA; j += i)
                if (!lpf[j]) lpf[j] = i;
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        // Group indices by prime factor
        unordered_map<int, vector<int>> pd;
        pd.reserve(n * 2);
        pd.max_load_factor(0.7f);
        for (int i = 0; i < n; i++) {
            int x = a[i];
            vector<int> primes;
            while (x > 1) {
                int p = lpf[x];
                primes.push_back(p);
                while (x % p == 0) x /= p;
            }
            for (int p : primes) pd[p].push_back(i);
        }

        // Build adjacency by chaining each prime's sorted indices
        vector<vector<int>> adj(n);
        ll totalEdges = 0;
        for (auto &kv : pd) {
            auto &v = kv.second;
            sort(v.begin(), v.end());
            for (int i = 1; i < (int)v.size(); i++) {
                int u = v[i-1], w = v[i];
                adj[u].push_back(w);
                adj[w].push_back(u);
                totalEdges++;
            }
        }

        // BFS bipartiteness check and component count
        vector<int> color(n, -1);
        bool ok = true;
        int comps = 0;
        for (int i = 0; i < n && ok; i++) {
            if (color[i] != -1) continue;
            comps++;
            queue<int> q;
            color[i] = 0;
            q.push(i);
            while (!q.empty() && ok) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        ok = false;
                        break;
                    }
                }
            }
        }

        if (!ok) {
            cout << 0 << '\n';
        } else {
            ll ans;
            if (totalEdges == 0) {
                // no constraints
                ans = (modexp(2, n) - 2 + MOD) % MOD;
            } else {
                ans = modexp(2, comps);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
