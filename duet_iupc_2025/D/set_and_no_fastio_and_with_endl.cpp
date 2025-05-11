#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;

        // Insert all characters into a set
        set<char> st;
        for (auto c: s) st.insert(c);
        // If the set size equals string length, all chars are distinct
        cout << (st.size() == s.size() ? "YES" : "NO") << endl;
    }

    return 0;
}
