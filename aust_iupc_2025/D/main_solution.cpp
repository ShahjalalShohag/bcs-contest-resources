#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e5+5;

int n, par[sz], val[sz], rnk[sz];
vector <int> g[sz];

int dep[sz], beg[sz], fin[sz], who[sz], kid;

ll tree[sz << 2], ex[sz << 2], ans[sz];
const ll inf = 1e13;

void init(int u = 1, int b = 1, int e = n) {
   ex[u] = 0;
   if(b == e) {
      tree[u] = -inf * (1 + dep[who[b]]);
      return;
   }
   int m = b + e >> 1, x = u << 1, y = x + 1;
   init(y, m + 1, e); init(x, b, m);
   tree[u] = max(tree[x], tree[y]);
}

void push(int u, int b, int e) {
   tree[u] += ex[u];
   if(b ^ e) ex[u << 1] += ex[u], ex[u << 1 | 1] += ex[u];
   ex[u] = 0;
}

void update(int l, int r, ll w, int u = 1, int b = 1, int e = n) {
   if(ex[u]) push(u, b, e);
   if(e < l or r < b or l > r) return;
   if(l <= b and e <= r) {
      ex[u] += w;
      return push(u, b, e);
   }
   int m = b + e >> 1, x = u << 1, y = x + 1;
   update(l, r, w, x, b, m);
   update(l, r, w, y, m + 1, e);
   tree[u] = max(tree[x], tree[y]);
}

ll query(int l, int r, int u = 1, int b = 1, int e = n) {
   if(ex[u]) push(u, b, e);
   if(e < l or r < b or l > r) return -inf * n;
   if(l <= b and e <= r) return tree[u];
   int m = b + e >> 1, x = u << 1, y = x + 1;
   return max(query(l, r, x, b, m), query(l, r, y, m + 1, e));
}

void dfs(int u, int p) {
   beg[u] = ++kid, who[kid] = u;
   for(int v : g[u]) dep[v] = 1 + dep[u], dfs(v, u);
   fin[u] = kid;
}

void solve() {
   scanf("%d", &n);
   for(int i=1; i<=n; i++) g[i].clear();
   for(int i=2; i<=n; i++) scanf("%d", &par[i]), g[par[i]].push_back(i);
   for(int i=1; i<=n; i++) scanf("%d", &val[i]);
   for(int i=1; i<=n; i++) scanf("%d", &rnk[i]);
   
   kid = 0;
   dfs(1, 0);
   init();

   vector <int> id(n);
   iota(id.begin(), id.end(), 1);
   sort(id.begin(), id.end(), [] (int u, int v) {
      return rnk[u] < rnk[v];
   });
   
   for(int u : id) {
      update(beg[u], fin[u], val[u] + inf);

      vector <ll> childs;
      ll pref = query(beg[u], beg[u]);
      for(int v : g[u]) {
         ll res = query(beg[v], fin[v]) - pref;
         if(res > 0) childs.push_back(res);
      }
      sort(childs.begin(), childs.end(), greater<ll>());

      ans[u] = val[u];
      if(childs.size() > 0) ans[u] += childs[0];
      if(childs.size() > 1) ans[u] += childs[1];
   }

   for(int i=1; i<=n; i++) printf("%lld ", ans[i]); puts("");
}

int main() {
   int t;
   cin >> t;
   while(t--) solve();
}