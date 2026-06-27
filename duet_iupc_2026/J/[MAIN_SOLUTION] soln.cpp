#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        bool ok = true;

        for (int i = 1; i <= n; i++) {
            long long x;
            cin >> x;
            if (x > i) ok = false;
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}