#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;

        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a'] ^= 1;
        }

        bool flag = 0;
        for(int i = 0; i < 26; i++) {
            flag |= cnt[i];
        }

        cout << (flag? "NO" : "YES") << "\n";
    }
}