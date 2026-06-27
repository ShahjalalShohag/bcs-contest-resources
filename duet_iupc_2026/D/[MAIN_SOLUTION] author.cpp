#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;
    
    int a, b, c;
    cin >> a >> b >> c;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> dc(n + 1, -1);
    queue<int> q;
    
    q.push(c);
    dc[c] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dc[v] == -1) {
                dc[v] = dc[u] + 1;
                q.push(v);
            }
        }
    }
    
    if (dc[a] != -1 && dc[b] != -1) {
        if (dc[a] < dc[b]) cout << "Alice\n";
        else if (dc[a] > dc[b]) cout << "Bob\n";
        else cout << "Tie\n";
    } 
    else if (dc[a] != -1 && dc[b] == -1) {
        cout << "Alice\n";
    } 
    else if (dc[a] == -1 && dc[b] != -1) {
        if (dc[b] > 1) cout << "Alice\n";
        else cout << "Tie\n";
    } 
    else {
        vector<int> da(n + 1, -1);
        q.push(a);
        da[a] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (da[v] == -1) {
                    da[v] = da[u] + 1;
                    q.push(v);
                }
            }
        }
        
        if (da[b] != -1) cout << "Alice\n";
        else cout << "Tie\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}