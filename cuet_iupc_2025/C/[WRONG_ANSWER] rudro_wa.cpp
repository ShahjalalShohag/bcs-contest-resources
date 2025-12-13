#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        int freq[26] = {0};
        for (char c : s) freq[c - 'a']++;

        bool ok = true;
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 != 0) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
