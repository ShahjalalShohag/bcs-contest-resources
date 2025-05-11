#include<bits/stdc++.h>

using namespace std;

int val[300005], cnt;
vector<int> adj[300005];

void dfs(int u, int p) {
    for(auto v : adj[u]) {
        if(v == p) continue;
        dfs(v, u);
        cnt += val[v];
        val[u] ^= val[v];
    }
}

void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
        adj[i].clear();
    }
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cnt = 0;
    dfs(1, 0);
    if(val[1]) cnt = -1;

    cout << cnt << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
