#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int INF  = 1000000007;

int n;
int a[MAXN];
vector<int> adj[MAXN];

// dp[u][p_flip][final_u_bit] = min ops to zero out subtree(u),
// given that the edge to parent is flipped p_flip times (mod2),
// and u’s own final bit (after all flips) is final_u_bit (0 or 1).
int dp[MAXN+1][2][2];

void dfs(int u, int p) {
    for(int p_flip = 0; p_flip < 2; p_flip++){
      for(int uf = 0; uf < 2; uf++){
        dp[u][p_flip][uf] = ((a[u] ^ p_flip ^ uf) == 0 ? 0 : INF);
      }
    }

    for(int v: adj[u]) {
        if(v == p)
            continue;

        dfs(v, u);
        int tmp[2][2];
        for(int p_flip = 0; p_flip < 2; p_flip++)
          for(int uf = 0; uf < 2; uf++)
            tmp[p_flip][uf] = INF;

        for(int p_flip=0;p_flip<2;p_flip++){
        for(int uf=0; uf<2; uf++){
          if(dp[u][p_flip][uf] >= INF) continue;
          for(int ep=0; ep<2; ep++){
            int cost_uv = dp[u][p_flip][uf] + ep;
            int new_uf  = uf ^ ep;
            int child_cost = dp[v][ep][0];
            if(child_cost >= INF) continue;
            tmp[p_flip][new_uf] = min(tmp[p_flip][new_uf], cost_uv + child_cost);
          }
        }}
        
        for(int p_flip=0;p_flip<2;p_flip++)
          for(int uf=0;uf<2;uf++)
            dp[u][p_flip][uf] = tmp[p_flip][uf];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            adj[i].clear();
        }
        for(int i = 1; i < n; i++){
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0);

        int ans = dp[1][0][0];
        if(ans >= INF) ans = -1;
        
        cout << ans << "\n";
    }
    return 0;
}
