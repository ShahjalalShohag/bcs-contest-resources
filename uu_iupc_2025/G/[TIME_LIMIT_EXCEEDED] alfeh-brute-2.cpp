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
        std::vector<int> last_index(n + 1, n);
        std::vector<int> next_high(n + 1, n);
        for(int &u:v) cin >> u;
        for(int i = n - 1; i >= 0; i--) {
            for(int j = v[i] + 1; j <= n; j++) {
                next_high[i] = min(next_high[i], last_index[j]);
            }
            last_index[v[i]] = i;
        } 
        for(int i = 0; i < n; i++) {
            if(v[i] > 0) continue;
            int j = i; 
            int mx = 0;
            int zero_count = next_high[i] - i;
            ans += zero_count * (zero_count + 1) / 2;
            ans -= zero_count * zero_count;
            while(j < n) {
                int next_j = next_high[j];
                ans += 1LL * (v[j] + 1) * (next_j - j) * zero_count;
                if(v[next_j] > v[j] + 1) {
                    ans += 1LL * (v[j] + 1) * (n - next_j) * zero_count;
                    break;
                }
                j = next_j;
            }
            i += zero_count;
        }
        cout << ans << "\n";
    }
    return 0;
}
