#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;
const int MAX = 600005;

vector<ll> invs;

struct DSU {
    unordered_map<int, int> parent, vertices, edges;
    ll ans = 1;
    bool bad = false;

    void make(int x) {
        if (parent.count(x)) return;
        parent[x] = x;
        vertices[x] = 1;
        edges[x] = 0;
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    int contribution(int r) {
        if (edges[r] == vertices[r] - 1) return vertices[r];
        if (edges[r] == vertices[r]) return 2;
        return 0;
    }

    void add_component(int r) {
        int cur = contribution(r);
        if (cur == 0) bad = true;
        else ans = ans * cur % MOD;
    }

    void remove_component(int r) {
        int cur = contribution(r);
        if (cur != 0) ans = ans * invs[cur] % MOD;
    }

    void add_edge(int a, int b) {
        if (bad) return;

        make(a);
        make(b);
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

    DSU dsu;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        dsu.add_edge(x, y);
        cout << (dsu.bad ? 0 : dsu.ans) << " \n"[i + 1 == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    invs.assign(MAX, 1);
    for (int i = 2; i < MAX; i++) {
        invs[i] = MOD - (MOD / i) * invs[MOD % i] % MOD;
    }

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
