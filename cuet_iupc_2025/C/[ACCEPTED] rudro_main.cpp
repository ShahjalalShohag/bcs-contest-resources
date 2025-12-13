#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    assert(1 <= t && t <= 10000);

    long long total_len = 0;

    while (t--) {
        string s;
        cin >> s;

        int n = s.size();
        assert(1 <= n && n <= 300000);

        total_len += n;
        assert(total_len <= 300000);

        for (char c : s) assert(c >= 'a' && c <= 'z');

        string st;
        st.reserve(n);

        for (char c : s) {
            if (!st.empty() && st.back() == c) st.pop_back();
            else st.push_back(c);
        }

        cout << (st.empty() ? "YES" : "NO") << '\n';
    }

    return 0;
}
