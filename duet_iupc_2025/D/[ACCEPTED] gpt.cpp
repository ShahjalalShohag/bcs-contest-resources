#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        // If any character repeats, 's' is not interesting
        vector<bool> seen(26, false);
        bool ok = true;
        for (char c : s) {
            int idx = c - 'a';
            if (seen[idx]) {
                ok = false;
                break;
            }
            seen[idx] = true;
        }
        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}
