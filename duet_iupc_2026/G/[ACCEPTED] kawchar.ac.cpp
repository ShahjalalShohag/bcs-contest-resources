#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353
#define MAX 1000005
typedef long long ll;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    ll ans = min(n, k);
    
    if (m % 2== 0) ans = min(ans, n * m - k);

    ans -= abs(ans % 2 - k % 2);

    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}