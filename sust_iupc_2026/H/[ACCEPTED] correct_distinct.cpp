#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// A single distinct letter means every pair of substrings is comparable, so the answer is 0.

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    set<char> letters(s.begin(), s.end());
    cout << (letters.size() <= 1 ? 0 : 2 * n - 2) << '\n';
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
