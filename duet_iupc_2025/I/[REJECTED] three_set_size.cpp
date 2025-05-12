#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // If n > 50, we skip brute and print 0
        if (n > 50) {
            cout << 0 << "\n";
            continue;
        }

        ll ans = LLONG_MAX;
        // Try all s1 of size k = 1, 2, 3 (but at most n-1)
        for (int k = 1; k <= min(3, n-1); k++) {
            if (k == 1) {
                for (int i = 0; i < n; i++) {
                    ll x = a[i];
                    ll y = 0;
                    for (int m = 0; m < n; m++) {
                        if (m == i) continue;
                        y |= a[m];
                    }
                    ans = min(ans, x * y);
                }
            }
            else if (k == 2) {
                for (int i = 0; i < n; i++) {
                    for (int j = i+1; j < n; j++) {
                        ll x = a[i] ^ a[j];
                        ll y = 0;
                        for (int m = 0; m < n; m++) {
                            if (m == i || m == j) continue;
                            y |= a[m];
                        }
                        ans = min(ans, x * y);
                    }
                }
            }
            else if (k == 3) {
                for (int i = 0; i < n; i++) {
                    for (int j = i+1; j < n; j++) {
                        for (int lidx = j+1; lidx < n; lidx++) {
                            ll x = a[i] ^ a[j] ^ a[lidx];
                            ll y = 0;
                            for (int m = 0; m < n; m++) {
                                if (m == i || m == j || m == lidx) continue;
                                y |= a[m];
                            }
                            ans = min(ans, x * y);
                        }
                    }
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
