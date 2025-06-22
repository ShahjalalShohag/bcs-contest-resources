#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
const int N = 2e5 + 5, mod = 1e9 + 7;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        long long int ans = 0;
        std::vector<int> v(n);
        for(int &u:v) cin >> u;
        for(int i = 0; i < n; i++) {
            if(v[i] > 0) continue;
            int j = i;
            while(j < n && v[j] == 0) j++;
            int mx = 0;
            int zero = j - i;
            ans += 1LL * zero * (zero + 1) / 2;
            while(j < n) {
                int last_max = mx;
                mx = max(mx, v[j]);
                if(mx <= last_max + 1) {
                    ans += 1LL * zero * (mx + 1);
                    j++;
                } else {
                    ans += 1LL * zero * (last_max + 1) * (n - j);
                    break;
                }
            }
            i += zero;
        }
        cout << ans << "\n";
    }
    return 0;
}
