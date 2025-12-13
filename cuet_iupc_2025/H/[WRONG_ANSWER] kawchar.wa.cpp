#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXP = 10000001; //8265139 + 10;

static bitset<MAXP> siv;
vector<int> primes, twins;

void sieve_primes() {
    siv.reset();    
    for (int i = 3; (ll)i * i < MAXP; i += 2) {
        if (!siv[i]) {
            for (ll j = 1LL * i * i; j < MAXP; j += 2LL * i) siv[j] = 1;
        }
    }

    primes.push_back(2);
    for (int i = 3; i < MAXP; i += 2) if (!siv[i]) primes.push_back(i);
}

void print_sample_3() {
    cout << "4\n";
    cout << "12 6\n";
    cout << "7 12\n";
    cout << "9 6\n";
    cout << "6 8\n";
    cout << "2 3 4\n";
    cout << "1 3 4\n";
    cout << "1 2 4\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve_primes();

    for (int i = 1; i < (int)primes.size(); i++) {
        if (primes[i] - primes[i-1] == 2) {
            twins.push_back(primes[i]);
            i++;
        }
    }

    int T; cin >> T;

    while (T--) {
        int N; cin >> N;
        
        if (N == 3) {
            print_sample_3();
            continue;
        }
        
        int m = N / 2;
        int K = 3 + m;
        cout << K << '\n';
        cout << 0 << ' ' << 2 << '\n';
        cout << 0 << ' ' << 0 << '\n';
        cout << 2 << ' ' << 0 << '\n';
        for (int i = 0; i < m; ++i) {
            int p = twins[i];
            cout << p << ' ' << 0 << '\n';
        }

        int printed = 0;
        if (N % 2 == 1) {
            cout << 1 << ' ' << 2 << ' ' << 3 << '\n';
            ++printed;
        }

        for (int i = 0; i < m && printed < N; ++i) {
            int idx = 4 + i;
            
            cout << 1 << ' ' << 2 << ' ' << idx << '\n';
            ++printed;
            if (printed >= N) break;
            cout << 1 << ' ' << 3 << ' ' << idx << '\n';
            ++printed;
        }
    }

    return 0;
}