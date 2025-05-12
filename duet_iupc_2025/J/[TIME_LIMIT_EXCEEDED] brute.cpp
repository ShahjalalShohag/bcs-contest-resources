#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;

// Compute gcd and lcm
ll gcd_ll(ll a, ll b) {
    return b == 0 ? a : gcd_ll(b, a % b);
}
ll lcm_ll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return a / gcd_ll(a,b) * b;
}

// Sum of distinct prime factors of x
int sumDistinctPrimes(ll x) {
    int sum = 0;
    if (x % 2 == 0) {
        sum += 2;
        while (x % 2 == 0) x /= 2;
    }
    for (ll p = 3; p*p <= x; p += 2) {
        if (x % p == 0) {
            sum += p;
            while (x % p == 0) x /= p;
        }
    }
    if (x > 1) sum += x;
    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> comb;
        ll answer = 0;

        // recursive combination generator
        function<void(int)> dfs = [&](int start) {
            if ((int)comb.size() == k) {
                // compute lcm of a[comb[0..k-1]]
                ll L = 1;
                for (int idx : comb) {
                    L = lcm_ll(L, a[idx]);
                    if (L == 0) break;
                }
                // factor and sum primes
                int s = sumDistinctPrimes(L);
                answer = (answer + s) % MOD;
                return;
            }
            // try taking further elements
            for (int i = start; i < n; i++) {
                comb.push_back(i);
                dfs(i+1);
                comb.pop_back();
            }
        };

        dfs(0);

        cout << answer << "\n";
    }

    return 0;
}
