#include <bits/stdc++.h>
using namespace std;
 
typedef long long          ll;
typedef unsigned long long ull;
 
ull mod = 998'244'353;
 
const int MAX = 65;
ull comb[MAX][MAX];
 
ull binpow(ull b, ull p) {
    b %= mod;
    ull ans = 1;
    while (p) {
       if (p & 1) ans = ans * b % mod;
       b = b * b % mod;
       p >>= 1;
    }
    return ans;
}
 
ull nCr(int n, int r) {
    if (min(n,r) < 0 || r > n) return 0;
    auto &val = comb[n][r];
    if (val != -1) return val;
    return val = (nCr(n-1, r) + nCr(n-1, r-1)) % mod;
}
 
void pre() {
    memset(comb, -1, sizeof comb);
    comb[0][0] = 1;
}
 
void solve() {
    ull n, m;
    cin >> n >> m;
    
    vector<ull> popcount_sum(MAX, 0);
    
    int pre_sum = 0;
    for (ull k = 1ULL << 63, j = 63; k > 0; k >>= 1, j--)
    {
        if (m & k) {
            for (int x = 0; x <= j; x++)
            {
                popcount_sum[x + pre_sum] += nCr(j,x) % mod;
            }
            
            pre_sum++;
        }
    }
    
    popcount_sum[pre_sum] += 1;
    
    ull ans = 1;
    
    for (int i = 1; i < MAX; i++) {
        if (popcount_sum[i]) {
            ans += (popcount_sum[i] % mod) * binpow(n, i) % mod;
        }
    }
    
    cout << ans % mod << "\n";
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    pre();
    
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}
