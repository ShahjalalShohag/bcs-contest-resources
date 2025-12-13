#include <bits/stdc++.h>
using namespace std;

bool solve_line(int L, int a, int b) {
    // a < b are 1-indexed positions of zeros in a 1D array of ones
    vector<int> v(L+1, 1);
    v[a] = 0;
    v[b] = 0;

    // simulate edge flows
    vector<long long> x(L, 0);

    x[1] = v[1];
    if (x[1] < 0) return false;

    for (int i = 2; i <= L-1; i++) {
        x[i] = v[i] - x[i-1];
        if (x[i] < 0) return false;
    }

    // final consistency check
    return x[L-1] == v[L];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, m, r1, c1, r2, c2;
        cin >> n >> m >> r1 >> c1 >> r2 >> c2;

        if (n == 1 || m == 1) {
            int L = (n == 1 ? m : n);
            int p1 = (n == 1 ? c1 : r1);
            int p2 = (n == 1 ? c2 : r2);
            if (p1 > p2) swap(p1, p2);

            cout << (solve_line(L, p1, p2) ? "YES\n" : "NO\n");
            continue;
        }

        // 2D case
        if ((n*m) % 2 == 0 &&
            ((r1 + c1) % 2) != ((r2 + c2) % 2))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}