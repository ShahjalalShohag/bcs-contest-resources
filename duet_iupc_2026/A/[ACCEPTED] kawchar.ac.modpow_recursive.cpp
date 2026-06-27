#include <bits/stdc++.h>
using namespace std;
 
#define MOD 998244353
#define MAX 600005
 
typedef long long ll;
 
vector<ll> invs;

ll modpow(ll a, ll b) {
    if (b == 0) return 1;

    ll half = modpow(a, b / 2);
    ll res = half * half % MOD;

    if (b & 1) res = res * a % MOD;

    return res;
}
 
struct DSU {
    vector<int> parent, vertices, edges;
    ll ans;
    int bad_components;
 
    DSU(int n = 0) {
        parent.resize(n);
        vertices.resize(n);
        edges.resize(n);
 
        ans = 1;
        bad_components = 0;
 
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            vertices[i] = 1;
            edges[i] = 0;
        }
    }
 
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
 
    int contribution(int r) {
        if (edges[r] == vertices[r] - 1) return vertices[r];
        if (edges[r] == vertices[r]) return 2;
        return 0;
    }
 
    void add_component(int r) {
        int cur = contribution(r);
 
        if (cur == 0) bad_components++;
        else ans = ans * cur % MOD;
    }
 
    void remove_component(int r) {
        int cur = contribution(r);
 
        if (cur == 0) bad_components--;
        else ans = ans * invs[cur] % MOD;
    }
 
    void add_edge(int a, int b) {
        a = find(a);
        b = find(b);
 
        if (a == b) {
            remove_component(a);
            edges[a]++;
            add_component(a);
            return;
        }
 
        remove_component(a);
        remove_component(b);
 
        if (vertices[a] < vertices[b]) swap(a, b);
 
        parent[b] = a;
        vertices[a] += vertices[b];
        edges[a] += edges[b] + 1;
 
        add_component(a);
    }
};
 
void solve() {
    int n;
    cin >> n;
 
    vector<pair<ll, ll>> input(n);
    vector<ll> vals;
    vals.reserve(2 * n);
 
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
 
        input[i] = {x, y};
        vals.push_back(x);
        vals.push_back(y);
    }
 
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
 
    map<ll, int> id;
    for (int i = 0; i < (int)vals.size(); i++) {
        id[vals[i]] = i;
    }
 
    vector<pair<int, int>> edges(n);
    for (int i = 0; i < n; i++) {
        edges[i] = {id[input[i].first], id[input[i].second]};
    }
 
    DSU dsu(vals.size());
 
    for (int i = 0; i < n; i++) {
        dsu.add_edge(edges[i].first, edges[i].second);
 
        if (dsu.bad_components > 0) cout << 0;
        else cout << dsu.ans;
 
        cout << " \n"[i + 1 == n];
    }
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    invs.assign(MAX, 1);
    for (int i = 2; i < MAX; i++) {
        invs[i] = modpow(i, MOD - 2);
    }
 
    int TC = 1;
    cin >> TC;
 
    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }
 
    return 0;
}
