#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MX = 1e7 + 5;
static int spf[MX], mu[MX];
vector<int> primes;

void build_sieve() {
    mu[1] = 1;
    for (int i = 2; i < MX; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            mu[i] = -1;
            primes.push_back(i);
        }
        for (int p : primes) {
            ll v = 1LL * i * p;
            if (v >= MX) break;
            spf[v] = p;
            mu[v] = (spf[i] == p ? 0 : -mu[i]);
            if (spf[i] == p) break;
        }
    }
}

vector<int> gen_divs(int x) {
    vector<pair<int,int>> fac;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) { x /= p; ++cnt; }
        fac.emplace_back(p, cnt);
    }
    vector<int> divs = {1};
    for (auto &pr : fac) {
        int p = pr.first, cnt = pr.second;
        int sz = divs.size();
        ll power = 1;
        for (int e = 1; e <= cnt; ++e) {
            power *= p;
            for (int i = 0; i < sz; ++i)
                divs.push_back(divs[i] * power);
        }
    }
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_sieve();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int A = 0;
        for (int &x : a) {
            cin >> x;
            A = max(A, x);
        }

        vector<int> freq(A+1, 0);
        for (int x : a) freq[x]++;

        vector<ll> multCnt(A+1, 0);
        for (int v = 1; v <= A; ++v) {
            if (freq[v] > 0) {
                auto dv = gen_divs(v);
                for (int d : dv) {
                    multCnt[d] += freq[v];
                }
            }
        }

        sort(a.begin(), a.end());
        ll ans = 0;
        for (int x: a) if (x == 1) ans++;

        for (int x : a) {
            // remove x
            auto dx = gen_divs(x);
            for (int d : dx) {
                multCnt[d]--;
            }

            // count pairs with this x as the smaller
            for (int g : dx) {
                if ((ll)g * g > x) continue;
                if (x % (g * g) != 0) continue;
                int xprime = x / g;
                auto dpx = gen_divs(xprime);
                ll cnt = 0;
                for (int d : dpx) {
                    int idx = g * d;
                    if (idx <= A) cnt += mu[d] * multCnt[idx];
                }
                ans += cnt;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
