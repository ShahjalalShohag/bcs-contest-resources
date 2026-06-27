#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 300005

typedef long long ll;

void solve() {
    int n; cin >> n;

    ll left = 0, right = 0, diagonal = 0;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        if (x < y) {
            left++;
        } else if (x > y) {
            right++;
        } else {
            diagonal++;
        }
    }

    ll ans = 0;
    ans += left * right;
    ans += diagonal * (left + right);
    ans += diagonal * (diagonal - 1) / 2;

    cout << ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
