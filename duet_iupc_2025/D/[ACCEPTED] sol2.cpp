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

        bool interesting = true;
        for (int i = 0; i < n && interesting; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    interesting = false;
                    break;
                }
            }
        }

        cout << (interesting ? "YES\n" : "NO\n");
    }

    return 0;
}
