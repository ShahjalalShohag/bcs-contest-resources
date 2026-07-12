#include<bits/stdc++.h>
using namespace std;

// (b,d) framing: the count for a fixed b is (tau(b^2)-1)/2; here tau(b^2) comes from factorizing
// b through a smallest-prime-factor sieve. Prefix-sum for all n.

const int N = 2e6 + 9;
using ll = long long;

int spf[N], ans[N];

void precompute() {
    for (int i = 2; i < N; i++)
        if (!spf[i])
            for (int j = i; j < N; j += i)
                if (!spf[j]) spf[j] = i;
    for (int b = 2; b < N; b++) {
        int x = b, t2 = 1;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) { x /= p; e++; }
            t2 *= (2 * e + 1);
        }
        ans[b] = ans[b - 1] + (t2 - 1) / 2;
    }
}

void solve() {
    int n;
    cin >> n;
    cout << ans[n] << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    precompute();
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
