#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e6+5, mod = 998244353;

ll fac[sz], finv[sz], inv[sz];

ll bigmod(ll b, ll n) {
   b %= mod;
   if(n == -1) n = mod - 2;
   ll ans = 1;
   while(n) {
      if(n & 1) ans = ans * b % mod;
      n >>= 1;
      b = b * b % mod;
   }
   return ans;
}

void prec() {
   inv[0] = inv[1] = 1;
   for(int i=2; i<sz; i++)
      inv[i] = mod - mod / i * inv[mod % i] % mod;
   fac[0] = finv[0] = 1;
   for(int i=1; i<sz; i++) {
      fac[i] = fac[i-1] * i % mod;
      finv[i] = finv[i-1] * inv[i] % mod;
   }
}

int up[sz], cnt[sz];
ll res[sz];

void solve() {
   int n, m, q;
   scanf("%d %d %d", &n, &m, &q);

   set <int> st;
   ll ans = 1; int pos = n;
   while(q--) {
      int l, r;
      scanf("%d %d", &l, &r);

      auto it = st.upper_bound(l);
      if(it != st.begin() and up[*prev(it)] >= r) {
         printf("%lld\n", ans * bigmod(m, pos) % mod);
         continue;
      }
      
      if(!up[l]) it = st.insert(l).first;
      else it--;
      up[l] = r;

      ll cut = 1;
      it++;
      while(it != st.end()) {
         int i = *it;
         if(up[i] <= r) {
            cut = cut * res[i] % mod;
            pos += cnt[i];
            up[i] = cnt[i] = 0, res[i] = 1;
            it = st.erase(it);
         }
         else break;
      }

      for(int c = 0; c < 2; c++) {
         if(it == st.end()) {
            it--;
            continue;
         }
         int l = *it, r = up[l];
         cut = cut * res[l] % mod;
         pos += cnt[l];
         int k = m, d = r - l + 1;
         if(it != st.begin()) {
            it--;
            int pl = *it, pr = up[pl];
            if(pr >= l) {
               k -= pr + 1 - l;
               d -= pr + 1 - l;
            }
         }
         res[l] = fac[k] * finv[k - d] % mod;
         cnt[l] = d;
         ans = ans * res[l] % mod;
         pos -= cnt[l];
      }

      ans = ans * bigmod(cut, -1) % mod;
      printf("%lld\n", ans * bigmod(m, pos) % mod);
   }

   for(int i : st) up[i] = cnt[i] = 0, res[i] = 1;
}

int main() {
   prec();
   for(int i=0; i<sz; i++) res[i] = 1;
   int t;
   cin >> t;
   while(t--) solve();
}