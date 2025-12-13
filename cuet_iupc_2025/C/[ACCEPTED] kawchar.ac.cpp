#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        string s;
        cin >> s;

        int p = -1;
        for (char c : s) {
            if (p >= 0 && s[p] == c) --p;
            else s[++p] = c;
        }

        cout << (p == -1 ? "YES" : "NO") << "\n";
    }
}