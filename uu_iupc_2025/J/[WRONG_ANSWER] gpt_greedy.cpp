#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    const ll BIG = 1000000000;  // 10^9

    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == -1) 
                a[i] = BIG;
        }

        ll ans = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && a[i] >= a[i-1]) {
                cur += a[i];
            } else {
                cur = a[i];
            }
            ans = max(ans, cur);
        }

        cout << ans << "\n";
    }
    return 0;
}
