#include "bits/stdc++.h"
using namespace std;

const int mod = 998244353;

long long modpow(long long base, int exponent) {
    long long ans = 1;
    while(exponent) {
        if(exponent & 1) {
            ans = (ans * base) % mod;
        }
        exponent >>= 1;
        base = (base * base) % mod;
    }
    return ans;
}

int solve(int a1, int n) {
    vector<pair<int,int>> fac;
    for(int i = 2; 1LL * i * i <= a1; i++) { 
        int cnt = 0;
        while(a1 % i == 0) {
            a1 /= i;
            ++cnt;
        }
        if(cnt > 0) fac.emplace_back(i, cnt);
    }
    if(a1 > 1) {
        fac.emplace_back(a1, 1);
    }
    long long ans = 1;
    for(auto [_, exp] : fac) {
        long long count = 0;
        count += (exp - 1) * (modpow(exp + 1, n - 1) - 2 * modpow(exp, n - 1) + modpow(exp - 1, n - 1) + 2 * mod) % mod;
        count += 2 * (modpow(exp + 1, n - 1) - modpow(exp, n - 1) + mod) % mod;
        count %= mod;
        ans = ans * count % mod;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int a1, n;
        cin >> a1 >> n;
        cout << solve(a1, n) << endl;
    }
    return 0;
}
