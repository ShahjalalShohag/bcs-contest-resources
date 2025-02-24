#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int n = s.size();
    for (int i = 0; i + 2 < n; i++) {
        string t = s.substr(i, 3);
        sort(t.begin(), t.end());
        if (t == "abc") {
            cout << 3 << '\n';
            return 0;
        }
    }
    return 0;
}