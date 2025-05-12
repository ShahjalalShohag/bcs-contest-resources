#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve() {

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(n > 20) {
        cout << "0\n";
    }
    else {
        int ans = LONG_LONG_MAX;
        for(int i = 1; i < (1LL << n) - 1; i++) {
            int part1 = 0;
            int part2 = 0;
            for(int j = 0; j < n; j++) {
                if(i & (1LL << j)) {
                    part1 ^= a[j];
                }
                else {
                    part2 |= a[j];
                }
            }
            ans = min(ans, part1 * part2);
        }
        cout << ans << "\n";
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while(t--) {
        solve();
    }
}