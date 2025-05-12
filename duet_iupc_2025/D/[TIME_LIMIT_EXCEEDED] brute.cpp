#include <bits/stdc++.h>
using namespace std;

// Pure brute‐force checker for “interesting” strings.
// For each nonempty substring t of s, counts f(t) by scanning s,
// and verifies |t| % f(t) == 0.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;

        bool interesting = true;
        // enumerate all substrings s[i..j]
        for (int i = 0; i < n && interesting; ++i) {
            for (int j = i; j < n && interesting; ++j) {
                int len = j - i + 1;
                string t = s.substr(i, len);

                // count occurrences f(t)
                int cnt = 0;
                for (int k = 0; k + len <= n; ++k) {
                    if (s.substr(k, len) == t) {
                        ++cnt;
                    }
                }

                // check divisibility
                if (cnt == 0 || (len % cnt) != 0) {
                    interesting = false;
                    break;
                }
            }
        }

        cout << (interesting ? "YES\n" : "NO\n");
    }

    return 0;
}
