#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;
const int logn = 20;

vector <int> adj[maxn];

int discover[maxn];
int depth[maxn];
int parent[logn][maxn];
int a[maxn];

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
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
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

    if(n == 1) {
        printf("\n");
        return;
    }

    sum = 0;
    for(int i = 1; i < n; i++) {
        a[i] = lca(a[i], a[i + 1]);
        sum += a[i];
    }
    // print the second sum
    printf("%lld ", sum);

    for(int i = 2; i < n; i++) {
        long long sum = 0;
        for(int j = 1; j <= n - i; j++) {
            if(discover[a[j]] > discover[a[j + 1]]) {
                a[j] = a[j + 1];
            }
            sum += a[j];
        }
        printf("%lld ", sum);
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