// wrong_any_local_max.cpp
// INTENTIONALLY WRONG solution — returns YES if there exists any interior local maximum
// (common mistaken approach). This will produce WA on many tests.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        bool has_local_max = false;
        for (int i = 1; i + 1 < n; ++i) {
            if (p[i] > p[i-1] && p[i] > p[i+1]) {
                has_local_max = true;
                break;
            }
        }

        // WRONG: assuming existence of any local maximum implies reducible to length 2
        cout << (has_local_max ? "YES\n" : "NO\n");
    }
    return 0;
}
