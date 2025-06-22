#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            int g = __gcd(a[i], a[j]);
            int l = a[i] * a[j] / g;
            int lbg = l / g;
            if (lbg % max(a[i], a[j]) == 0) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
}

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while(t--) {
        solve();
    }
}