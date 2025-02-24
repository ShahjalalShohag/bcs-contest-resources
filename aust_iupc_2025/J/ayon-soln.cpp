#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e6+5, mod = 998244353;

int m, pos;

ll ans, fac[sz], finv[sz], inv[sz];

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

set <pair <int, int>> st;

inline void fnc(set <pair <int, int>>::iterator it, bool f) {
   auto [l, r] = *it;
   int k = m, d = r - l + 1;
   if(it != st.begin()) {
      auto [pl, pr] = *prev(it);
      if(pr >= l) {
         k -= pr + 1 - l;
         d -= pr + 1 - l;
      }
   }
   // add this segment
   ll now = fac[k] * finv[k - d] % mod;
   int cnt = d;

   if(next(it) != st.end()) {
      auto [nl, nr] = *next(it);
      if(nl <= r) {
         {
            // remove current next segment
            int nk = m, nd = nr - nl + 1;
            if(it != st.begin()) {
               auto [pl, pr] = *prev(it);
               if(pr >= nl) {
                  nk -= pr + 1 - nl;
                  nd -= pr + 1 - nl;
               }
            }
            ll cut = fac[nk] * finv[nk - nd] % mod;
            now = now * bigmod(cut, -1) % mod;
            cnt -= nd;
         }
         {
            // add updated next segment
            int nk = m, nd = nr - nl + 1;
            if(r >= nl) {
               nk -= r + 1 - nl;
               nd -= r + 1 - nl;
            }
            ll add = fac[nk] * finv[nk - nd] % mod;
            now = now * add % mod;
            cnt += nd;
         }
      }
   }

   if(f) {
      ans = ans * now % mod;
      pos -= cnt;
   }
   else {
      ans = ans * bigmod(now, -1) % mod;
      pos += cnt;
   }
}

void solve() {
   int n, q;
   scanf("%d %d %d", &n, &m, &q);

   st.clear();
   ans = 1, pos = n;
   for(int i=1; i<=q; i++) {
      int l, r, k = m;
      scanf("%d %d", &l, &r);
      auto it = st.lower_bound(make_pair(l + 1, -1));
      
      if(it != st.begin()) {
         auto [pl, pr] = *prev(it);
         if(pr >= r) {
            printf("%lld\n", ans * bigmod(m, pos) % mod);
            continue;
         }
         if(pl >= l) {
            fnc(prev(it), 0);
            st.erase(prev(it));
         }
      }

      ll cut = 1;
      while(it != st.end()) {
         auto [nl, nr] = *it;
         if(nr <= r) {
            fnc(it, 0);
            it = st.erase(it);
         }
         else break;
      }

      fnc(st.emplace(l, r).first, 1);
      printf("%lld\n", ans * bigmod(m, pos) % mod);
   }
}

int main() {
   prec();
   int t;
   cin >> t;
   while(t--) solve();
}