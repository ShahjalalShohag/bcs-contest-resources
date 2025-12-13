#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        
        bool changed = true;
        while (changed) {
            changed = false;
            int n = (int)s.size();
            for (int i = 0; i + 1 < n; ++i) {
                int l = i, r = i + 1;
                while (l >= 0 && r < n && s[l] == s[r]) {
                    s.erase(l, r - l + 1);
                    changed = true;
                    break;
                }
                if (changed) break;
            }
        }
        cout << (s.empty() ? "YES" : "NO") << '\n';
    }
    return 0;
}
