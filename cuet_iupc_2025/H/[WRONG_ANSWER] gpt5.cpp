#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    vector<int> ns(T);
    int maxn = 0;
    for (int i = 0; i < T; i++) {
        cin >> ns[i];
        maxn = max(maxn, ns[i]);
    }

    // We need up to 2 * ceil(maxn / 2) primes <= 100000
    // Sieve up to 3e6 which definitely has > 100000 primes.
    const int LIM = 3000000;
    vector<bool> is_prime(LIM + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * 1LL * i <= LIM; ++i) {
        if (is_prime[i]) {
            for (int j = i * 1LL * i; j <= LIM; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    primes.reserve(200000);
    for (int i = 2; i <= LIM; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    // We are guaranteed primes.size() > 100000 for LIM = 3e6.

    for (int tc = 0; tc < T; ++tc) {
        int n = ns[tc];
        int m = (n + 1) / 2;    // ceil(n/2)
        int k = 3 + m;          // total points

        cout << k << "\n";
        // Fixed three points
        cout << "0 0\n"; // P1
        cout << "1 0\n"; // P2
        cout << "0 1\n"; // P3

        // Extra points Q_j
        // Use first 2*m primes: primes[0..2m-1]
        for (int j = 0; j < m; ++j) {
            int p1 = primes[2 * j];
            int p2 = primes[2 * j + 1];
            int x = 2 * p1;
            int y = 2 * p2;
            cout << x << " " << y << "\n";
        }

        int printed = 0;
        for (int j = 0; j < m && printed < n; ++j) {
            int idx = 4 + j; // index of Q_j

            // Triangle with area = primes[2*j] (using P1, P3, Q_j)
            if (printed < n) {
                cout << 1 << " " << 3 << " " << idx << "\n";
                ++printed;
            }

            // Triangle with area = primes[2*j+1] (using P1, P2, Q_j)
            if (printed < n) {
                cout << 1 << " " << 2 << " " << idx << "\n";
                ++printed;
            }
        }
    }

    return 0;
}
