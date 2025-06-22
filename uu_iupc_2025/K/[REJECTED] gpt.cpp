#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 1000000;

int mu[MAXA+1];
bool is_comp[MAXA+1];
vector<int> primes;

void init_mobius() {
    mu[1] = 1;
    for (int i = 2; i <= MAXA; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            ll x = 1LL * i * p;
            if (x > MAXA) break;
            is_comp[x] = true;
            if (i % p == 0) {
                mu[x] = 0;
                break;
            } else {
                mu[x] = -mu[i];
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_mobius();

    int T;
    cin >> T;
    // Allocate freq and cnt once
    static int freq[MAXA+1];
    static int cnt[MAXA+1];

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int maxv = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            maxv = max(maxv, a[i]);
        }

        // build frequency
        for (int i = 0; i < n; i++) {
            freq[a[i]]++;
        }

        // compute cnt[d] = number of a[i] divisible by d
        for (int d = 1; d <= maxv; d++) {
            int c = 0;
            for (int m = d; m <= maxv; m += d) {
                c += freq[m];
            }
            cnt[d] = c;
        }

        // count unordered pairs i<j with gcd = 1
        ll pairs_coprime = 0;
        for (int d = 1; d <= maxv; d++) {
            int c = cnt[d];
            if (c >= 2 && mu[d] != 0) {
                // C(c, 2) = c*(c-1)/2
                pairs_coprime += (ll)mu[d] * ( (ll)c * (c - 1) / 2 );
            }
        }

        // self-pairs (i == j) count only when a[i] == 1
        ll self_ones = freq[1];

        // total pairs i <= j with gcd(a_i, a_j) = 1
        ll answer = pairs_coprime + self_ones;
        cout << answer << "\n";

        // clear freq and cnt up to maxv for next test
        for (int i = 0; i < n; i++) {
            freq[a[i]] = 0;
        }
        for (int d = 1; d <= maxv; d++) {
            cnt[d] = 0;
        }
    }

    return 0;
}
