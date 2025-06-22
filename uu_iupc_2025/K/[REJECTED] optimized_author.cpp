#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int MAXV = 600005;

int mu[MAXV + 1], spf[MAXV + 1];
vector<int> divisors[MAXV + 1];
vector<int> primes;

void init() {
    for (int i = 1; i <= MAXV; ++i) {
        for (int j = i; j <= MAXV; j += i) {
            divisors[j].push_back(i);
        }
    }
}

void build_mu() {
    mu[1] = 1;
    for (int i = 2; i <= MAXV; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (1LL * p * i > MAXV) break;
            spf[p * i] = p;
            mu[p * i] = (p == spf[i] ? 0 : -mu[i]);
            if (p == spf[i]) break;
        }
    }
}

int cntMul[MAXV + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_mu();
    init();

    int T;  cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        vector<pair<int, int>> unique_a;
        for (int &v : a) cin >> v;

        int ones = count(a.begin(), a.end(), 1);
        sort(a.begin(), a.end(), greater<int>());

        for (int i = 0; i < n; ++i) {
            if (unique_a.empty() || unique_a.back().first != a[i]) {
                unique_a.emplace_back(a[i], 1);
            } else {
                unique_a.back().second++;
            }
        }

        int64 ans = 0;
        for (auto [x, c] : unique_a) {

            for (int g : divisors[x]) {
                if (1LL * g * g > x) continue;
                if (x % (1LL * g * g)) continue;

                int m = x / g;
                int64 add = 0;
                for (int d : divisors[m])
                    add += 1LL * mu[d] * cntMul[g * d];

                ans += add * c;
            }

            for (int d : divisors[x]) {
                cntMul[d] += c;
            };
        }

        ans += (((int64)ones * (ones + 1)) / 2);

        for (int x : a)
            for (int d : divisors[x])
                cntMul[d] = 0;

        cout << ans << '\n';
    }
    return 0;
}
