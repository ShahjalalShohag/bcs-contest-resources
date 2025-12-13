#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int ans = INT_MAX;
        for (int i = 0; i < n - 2; i++) { // skipping last adjacent pair
            int score = a[i] ^ a[i + 1];
            ans = min(ans, score);
        }
        cout << ans << '\n';
    }
    return 0;
}
