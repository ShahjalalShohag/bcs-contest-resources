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

        // total XOR of all elements
        ll total_xor = 0;
        for (ll v : a) total_xor ^= v;

        // prefix_or[i] = OR of a[0..i]
        vector<ll> prefix_or(n), suffix_or(n);
        prefix_or[0] = a[0];
        for (int i = 1; i < n; i++) {
            prefix_or[i] = prefix_or[i-1] | a[i];
        }
        // suffix_or[i] = OR of a[i..n-1]
        suffix_or[n-1] = a[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix_or[i] = suffix_or[i+1] | a[i];
        }

        ll ans = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            // Case 1: single element a[i] in OR-set (s2)
            //   XOR(rest) * a[i]
            ll xor_except = total_xor ^ a[i];
            ans = min(ans, xor_except * a[i]);

            // Case 2: single element a[i] in XOR-set (s1)
            //   a[i] * OR(rest)
            ll or_except = 0;
            if (i > 0)  or_except |= prefix_or[i-1];
            if (i+1 < n) or_except |= suffix_or[i+1];
            ans = min(ans, a[i] * or_except);
        }

        cout << ans << "\n";
    }
    return 0;
}
