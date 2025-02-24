#include <iostream>
using namespace std;

const long long MOD = 998244353;

// 快速幂计算 (base^exp) % MOD
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

void solve() {
    long long a1, k;
    cin >> a1 >> k;
    
    long long ans = 1;
    
    for (long long p = 2; p * p <= a1; ++p) {
        if (a1 % p == 0) {
            long long exp = 0;
            while (a1 % p == 0) {
                a1 /= p;
                ++exp;
            }
            // 计算 (exp+1)^k - 2 * exp^k + (exp-1)^k
            long long term1 = power(exp + 1, k, MOD);
            long long term2 = 2LL * power(exp, k, MOD) % MOD;
            long long term3 = power(exp - 1, k, MOD);
            long long contrib = (term1 - term2 + term3 + MOD) % MOD;
            ans = ans * contrib % MOD;
        }
    }
    
    if (a1 > 1) { // 处理 a1 为质数的情况
        long long exp = 1;
        long long term1 = power(exp + 1, k, MOD);
        long long term2 = 2LL * power(exp, k, MOD) % MOD;
        long long term3 = power(exp - 1, k, MOD);
        long long contrib = (term1 - term2 + term3 + MOD) % MOD;
        ans = ans * contrib % MOD;
    }
    
    cout << ans << endl;
}

int main() {
    long long t;
    cin >> t;
    while (t--) solve();
    return 0;
}
