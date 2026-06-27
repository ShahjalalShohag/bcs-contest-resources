#include <bits/stdc++.h>
using namespace std;
 
typedef long long          ll;
typedef unsigned long long ull;
 
ull mod = 998'244'353;
 
void solve() {
    ull n, m;
    cin >> n >> m;
    
    ull p[65];
    p[0] = 1;
    ull n1 = (n + 1) % mod;
    for (int i = 1; i < 65; i++) {
        p[i] = (p[i - 1] * n1) % mod;
    }
    
    ull ans = 0;
    ull pow_n = 1;
    ull n_mod = n % mod;
    
    for (int i = 63; i >= 0; i--) {
        if ((m >> i) & 1ULL) {
            ull ways = (pow_n * p[i]) % mod;
            ans = (ans + ways) % mod;
            pow_n = (pow_n * n_mod) % mod; 
        }
    }
    ans = (ans + pow_n) % mod;
    
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}