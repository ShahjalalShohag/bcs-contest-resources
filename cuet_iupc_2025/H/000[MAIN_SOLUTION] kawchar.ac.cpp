#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXP = 10000001;

static bitset<MAXP> siv;
vector<int> primes, twins;

void build_twin_primes() {
    siv.reset();
    for (int i = 3; 1LL * i * i < MAXP; i += 2) {
        if (!siv[i]) {
            for (ll j = 1LL * i * i; j < MAXP; j += 2LL * i) {
                siv[j] = 1;
            }
        }
    }
    primes.push_back(2);
    for (int i = 3; i < MAXP; i += 2)
        if (!siv[i]) primes.push_back(i);

    for (int i = 1; i < (int)primes.size(); i++) {
        if (primes[i] - primes[i-1] == 2) {
            twins.push_back(primes[i]);
            i++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_twin_primes();

    int T; cin >> T;

    while (T--) {
        int N; cin >> N;

        int m = (N + 3) / 4;
        int K = 4 + m; 
        cout << K << "\n";

        cout << 0 << " " << 0 << "\n";
        cout << 2 << " " << 0 << "\n";
        cout << 0 << " " << 2 << "\n";
        cout << 2 << " " << 2 << "\n";

        for (int i = 0, tid = 0; i < m; i++) {
            int x = twins[tid++];
            int y = twins[tid++];
            cout << x << " " << y << "\n";
        }

        int printed = 0;
        for (int i = 0; i < m && printed < N; i++) {
            int idx = 5 + i;

            cout << 1 << " " << 3 << " " << idx << "\n"; printed++;
            if (printed >= N) break;

            cout << 1 << " " << 2 << " " << idx << "\n"; printed++;
            if (printed >= N) break;

            cout << 2 << " " << 4 << " " << idx << "\n"; printed++;
            if (printed >= N) break;

            cout << 3 << " " << 4 << " " << idx << "\n"; printed++;
        }
    }

    return 0;
}