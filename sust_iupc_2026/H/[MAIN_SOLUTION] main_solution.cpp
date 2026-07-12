#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// The answer is 2|s| - 2 when s has at least two distinct letters, else 0.

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    bool all_same = true;
    for (int i = 1; i < n; i++)
        if (s[i] != s[0]) { all_same = false; break; }
    cout << (all_same ? 0 : 2 * n - 2) << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
