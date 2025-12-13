#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        long long n, m, r1, c1, r2, c2;
        cin >> n >> m >> r1 >> c1 >> r2 >> c2;

        int p1 = (r1 + c1) % 2;
        int p2 = (r2 + c2) % 2;

        cout << (p1 != p2 ? "YES" : "NO") << "\n";
    }
    return 0;
}