#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while (t--) {
        string s;
        cin >> s;
        bool changed = true;
        while (changed) {
            changed = false;
            for (size_t i = 0; i + 1 < s.size(); ++i) {
                if (s[i] == s[i + 1]) {
                    s.erase(i, 2);
                    changed = true;
                    break;
                }
            }
        }
        cout << (s.empty() ? "YES" : "NO") << '\n';
    }
    return 0;
}
