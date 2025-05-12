#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int ca = 0, cb = 0, cs = 0;
        for (char c : s) {
            if (c == 'A') ++ca;
            else if (c == 'B') ++cb;
            else if (c == 'S') ++cs;
        }

        if (ca > 0 && cb > 0) {
            // both acids and bases present
            cout << 1 << "\n";
        } else if (cs > 0) {
            // salts plus only acids or only bases
            cout << 2 << "\n";
        } else {
            // only acids or only bases (no salts)
            cout << (ca + cb) << "\n";
        }
    }

    return 0;
}
