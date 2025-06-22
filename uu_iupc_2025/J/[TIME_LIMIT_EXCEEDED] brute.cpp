// Correct but TLE Brute-Force Solution
// Enumerate all subarrays [l..r], for each check if we can fill -1s to make it non-decreasing
// and compute the maximum possible sum by assigning each -1 the largest feasible value.
// Overall O(n^3) in the worst case.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    const ll BIG = 1000000000;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        ll ans = 0;
        // Try every subarray [l..r]
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                ll sum = 0;
                ll prev = 1;  // smallest possible value
                bool ok = true;
                // Check feasibility and compute best sum
                for (int k = l; k <= r; k++) {
                    if (a[k] != -1) {
                        // Known value
                        if (k > l && a[k] < prev) {
                            ok = false;
                            break;
                        }
                        prev = a[k];
                        sum += a[k];
                    } else {
                        // a[k] == -1, find next known or BIG
                        ll nxt = BIG;
                        for (int x = k + 1; x <= r; x++) {
                            if (a[x] != -1) {
                                nxt = a[x];
                                break;
                            }
                        }
                        ll upper = nxt;
                        ll lower = (k > l ? prev : 1);
                        if (lower > upper) {
                            ok = false;
                            break;
                        }
                        // Assign maximum feasible value
                        ll val = upper;
                        prev = val;
                        sum += val;
                    }
                }
                if (ok) ans = max(ans, sum);
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
