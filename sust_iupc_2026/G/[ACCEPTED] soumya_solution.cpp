#include <iostream>
#include <vector>
using namespace std;

const int N = 3e5 + 5;
vector<int> adj[N];
const int mod = 998244353;
int dp[N][3];

// 0 turned off in subtree
// 1 turned on in subtree
// 2 turned on in subtree but closed with parent

void dfs(int u, int p) {
    dp[u][1] = 1;
    dp[u][0] = 0;
    dp[u][2] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        dp[u][0] = (1LL * dp[u][0] * (dp[v][0] + dp[v][1]) + 1LL * dp[u][2] * dp[v][2]) % mod;
        dp[u][1] = (1LL * dp[u][1] * dp[v][0]) % mod;
        dp[u][2] = (1LL * dp[u][2] * (dp[v][0] + dp[v][1])) % mod;
    }
}

void testCase() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1);

    cout << (dp[1][0] + dp[1][1]) % mod << '\n';

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        dp[i][0] = 0;
        dp[i][1] = 0;
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        testCase();
    }
}