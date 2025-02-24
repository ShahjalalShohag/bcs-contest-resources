#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e5+5;
 
int par[sz], a[sz], r[sz];
ll cum[sz], ans[sz];
vector <int> g[sz];

struct dsu {
   int id[sz], top[sz];
   ll best[sz];
 
   void init(int n) {
      for(int i=1; i<=n; i++) id[i] = top[i] = i;
   }
 
   int root(int x) {
      return id[x] = id[x] ^ x ? root(id[x]) : x;
   }
 
   void unite(int x, int y) {
      ll val = cum[par[y]];
      x = root(x), y = root(y);
      val += best[y];
      if(top[x] > 1) val -= cum[par[top[x]]];
      id[y] = x;
      best[x] = max(best[x], val);
   }
} mst;
 
void dfs(int u) {
   for(int v : g[u]) cum[v] = cum[u] + a[v], dfs(v);
}
 
void solve() {
   int n;
   scanf("%d", &n);
   for(int i=1; i<=n; i++) g[i].clear();
   for(int i=2; i<=n; i++) {
      scanf("%d", &par[i]);
      g[par[i]].push_back(i);
   }
   for(int i=1; i<=n; i++) scanf("%d", &a[i]);
   for(int i=1; i<=n; i++) scanf("%d", &r[i]);
 
   cum[1] = a[1];
   dfs(1);
 
   vector <int> id(n);
   iota(id.begin(), id.end(), 1);
   sort(id.begin(), id.end(), [] (int u, int v) {
      return r[u] < r[v];
   });
 
   mst.init(n);
   for(int u : id) {
      ans[u] = mst.best[u] = a[u];
      for(int v : g[u]) if(r[v] < r[u]) {
         ans[u] = max(ans[u], mst.best[mst.root(u)] + mst.best[mst.root(v)]);
         mst.unite(u, v);
      }
 
      if(u > 1 and r[par[u]] < r[u]) {
         mst.unite(par[u], u);
      }
   }
   
   for(int i=1; i<=n; i++) printf("%lld ", ans[i]); puts("");
}
 
int main() {
   int t;
   cin >> t;
   while(t--) solve();
}
