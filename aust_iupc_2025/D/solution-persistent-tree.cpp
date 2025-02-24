#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll sz = 1e5+5, inf = 1e17;

int n, par[sz], val[sz], rnk[sz];
vector <int> g[sz];

int dep[sz], beg[sz], fin[sz], who[sz], kid;

int root[sz], tree[sz << 2];

ll cum[sz], ans[sz];

void update(int l, int r, int w, int u = 1, int b = 1, int e = n) {
   if(e < l or r < b) return;
   if(l <= b and e <= r) {
      if(dep[w] > dep[tree[u]]) tree[u] = w;
      return;
   }
   int m = b + e >> 1, x = u << 1, y = x + 1;
   update(l, r, w, x, b, m);
   update(l, r, w, y, m + 1, e);
}

void query(int i, int &v, int u = 1, int b = 1, int e = n) {
   if(i < b or i > e) return;
   if(dep[tree[u]] > dep[v]) v = tree[u];
   if(b == e) return;
   int m = b + e >> 1, x = u << 1, y = x + 1;
   query(i, v, x, b, m), query(i, v, y, m + 1, e);
}

struct PST {
   struct node {
      int l, r; 
      ll v;
   } tree[sz << 6];

   int k;

   int build(int b, int e) {
      int u = ++k;
      auto &now = tree[u];
      if(b == e) {
         now.v = cum[who[b]];
         return u;
      }
      int m = b + e >> 1;
      now.l = build(b, m);
      now.r = build(m + 1, e);
      now.v = max(tree[now.l].v, tree[now.r].v);
      return u;
   }

   int rebuild(int n) {
      k = 0;
      return build(1, n);
   }

   int update(int p, ll v, int l, int r, int b = 1, int e = n) {
      if(e < l or r < b) return p;
      int u = ++k;
      auto &now = tree[u];
      if(l <= b and e <= r) {
         now.v = v;
         return u;
      }
      int m = b + e >> 1;
      now.l = update(tree[p].l, v, l, r, b, m);
      now.r = update(tree[p].r, v, l, r, m + 1, e);
      now.v = max(tree[now.l].v, tree[now.r].v);
      return u;
   }

   ll query(int p, int l, int r, int b = 1, int e = n) {
      if(e < l or r < b) return -inf;
      if(l <= b and e <= r) return tree[p].v;
      int m = b + e >> 1;
      return max(query(tree[p].l, l, r, b, m), query(tree[p].r, l, r, m + 1, e));
   }
} pst;

void dfs(int u) {
   beg[u] = ++kid, who[kid] = u;
   for(int v : g[u]) dep[v] = 1 + dep[u], cum[v] = val[v] + cum[u], dfs(v);
   fin[u] = kid;
}

void solve() {
   scanf("%d", &n);
   for(int i=1; i<=n; i++) g[i].clear();
   for(int i=2; i<=n; i++) scanf("%d", &par[i]), g[par[i]].push_back(i);
   for(int i=1; i<=n; i++) scanf("%d", &val[i]);
   for(int i=1; i<=n; i++) scanf("%d", &rnk[i]);

   kid = 0;
   cum[1] = val[1], dep[1] = 1;
   dfs(1);

   vector <int> id(n);
   iota(id.begin(), id.end(), 1);
   sort(id.begin(), id.end(), [] (int u, int v) {
      return rnk[u] > rnk[v];
   });

   root[1] = pst.rebuild(n);
   for(int i=1; i<n<<2; i++) tree[i] = 0;
   update(1, n, 1);
   
   for(int u : id) {
      int rt = 0;
      query(beg[u], rt);

      vector <ll> childs;
      for(int v : g[u]) {
         ll res = pst.query(root[rt], beg[v], fin[v]) - cum[u];
         if(res > 0) childs.push_back(res);
      }
      sort(childs.begin(), childs.end(), greater<ll>());

      ans[u] = val[u];
      if(childs.size() > 0) ans[u] += childs[0];
      if(childs.size() > 1) ans[u] += childs[1];

      if(u != 1) {
         update(beg[u], fin[u], u);
         root[u] = root[rt];
         root[rt] = pst.update(root[rt], cum[par[u]], beg[u], fin[u]);
      }
   }

   for(int i=1; i<=n; i++) printf("%lld ", ans[i]); puts("");
}

int main() {
   int t;
   cin >> t;
   while(t--) solve();
}