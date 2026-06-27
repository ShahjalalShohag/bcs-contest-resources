#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n; cin >> n;

    bool possible = true;
    for (int i = 1; i <= n; i++)
    {
        ll in; cin >> in;
        if (in > i) {
            possible = false;
        }
    }
    
    cout << (possible ? "YES\n" : "NO\n");
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }

    return 0;

}