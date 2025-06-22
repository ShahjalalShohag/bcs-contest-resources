#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int MAXV = 1000000;

int mu[MAXV + 1], spf[MAXV + 1];
vector<int> primes;

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

vector<int> divisors(int x) {
    vector<pair<int,int>> fac;
    while (x > 1) {
        int p = spf[x], c = 0;
        while (x % p == 0) x /= p, ++c;
        fac.emplace_back(p, c);
    }
    vector<int> res{1};
    for (auto [p, e] : fac) {
        int sz = res.size();
        int64 cur = 1;
        for (int k = 1; k <= e; ++k) {
            cur *= p;
            for (int i = 0; i < sz; ++i)
                res.push_back(res[i] * cur);
        }
    }
    return res;
}

int cntMul[MAXV + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_mu();

    int T;  cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int &v : a) cin >> v;

        int ones = count(a.begin(), a.end(), 1);
        sort(a.begin(), a.end(), greater<int>());

        int64 ans = 0;
        for (int x : a) {
            auto divs = divisors(x);

            for (int g : divs) {
                if (1LL * g * g > x) continue;
                if (x % (1LL * g * g)) continue;

                int m = x / g;
                int64 add = 0;
                for (int d : divisors(m))
                    add += 1LL * mu[d] * cntMul[g * d];

                ans += add;
            }

            for (int d : divs) ++cntMul[d];
        }

        ans += ones;

        for (int x : a)
            for (int d : divisors(x))
                cntMul[d] = 0;

        cout << ans << '\n';
    }
    return 0;
}
