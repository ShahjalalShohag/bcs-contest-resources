#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;
const int logn = 20;

vector <int> adj[maxn];

int discover[maxn];
int depth[maxn];
int parent[logn][maxn];
int a[maxn];

long long pref[maxn], suff[maxn], cons[maxn];

// pass par=0 for root
void dfs(int x, int par, int &time) {
    discover[x] = ++time;
    parent[0][x] = par;
    for(int j = 1; j < logn; j++) {
        parent[j][x] = parent[j - 1][parent[j - 1][x]];
    }
    for (int u : adj[x]) {
        if (u != par) {
            depth[u] = depth[x] + 1;
            dfs(u, x, time);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    int diff = depth[u] - depth[v];
    for(int j = 0; j < logn; j++) {
        if (diff & (1 << j)) {
            u = parent[j][u];
        }
    }
    if (u == v) {
        return u;
    }
    for(int j = logn - 1; j >= 0; j--) {
        if (parent[j][u] != parent[j][v]) {
            u = parent[j][u];
            v = parent[j][v];
        }
    }
    return parent[0][u];
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n + 1; i++) {
        adj[i].clear();
        pref[i] = 0;
        suff[i] = 0;
        cons[i] = 0;
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int time = 0;
    depth[1] = 0;
    dfs(1, 0, time);

    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    // print the first sum
    printf("%lld ", sum);

    for(int i = 1; i < n; i++) {
        a[i] = lca(a[i], a[i + 1]);
    }

    vector<int> order (n-1);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [](int u, int v) {
        if (discover[a[u]] == discover[a[v]]) {
            return u < v;
        }
        return discover[a[u]] < discover[a[v]];
    });

    // 3 2 1
    // 3 1
    // 1

    // for i = 2
    // before = 0, after = 3
    // t1 = 2, t2 = 1
    // +1 +1 0

    set<int> processed;
    processed.insert(0);
    processed.insert(n);
    for(int i : order) {
        long long node = a[i];
        processed.insert(i);
        int before = *prev(processed.find(i));
        int after  = *next(processed.find(i));

        int t1 = i - before;
        int t2 = after - i;

        if (t1 > t2) {
            swap(t1, t2);
        }
        long long mult = 0;
        // for(int x = 0; x < t1; x++) {
        //     ans[x] += node * (x + 1);
        // }
        pref[0] += node;
        pref[t1] -= node;
        cons[t1] -= node * t1;

        // for(int x = t1; x < t2; x++) {
        //     ans[x] += node * t1;
        // }

        cons[t1] += node * t1;
        cons[t2] -= node * t1;

        // for(int x = t2; x < t1 + t2; x++) {
        //     ans[x] += node * (t1 + t2 - x - 1);
        // }
        suff[t1 + t2 - 2] += node;
        suff[t2 - 1] -= node;
        cons[0]  -= node * (t1 - 1);
        cons[t2] += node * (t1 - 1);
    }
    // double suffix sum for arithmetic progression
    for(int i = n; i >= 0; i--) {
        suff[i] += suff[i + 1];
    }
    for(int i = n; i >= 0; i--) {
        suff[i] += suff[i + 1];
    }
    // double prefix sum for arithmetic progression
    for(int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
    }
    // single prefix sum for constant part
    for(int i = 1; i <= n; i++) {
        cons[i] += cons[i - 1];
    }
    for(int x = 0; x < n-1; x++) {
        printf("%lld ", pref[x] + suff[x] + cons[x]);
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}