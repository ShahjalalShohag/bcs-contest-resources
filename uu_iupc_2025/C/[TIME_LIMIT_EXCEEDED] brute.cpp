#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1000005;

long long fact[MAXN], inv_fact[MAXN];

long long power(long long a, long long b, long long mod) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    inv_fact[MAXN-1] = power(fact[MAXN-1], MOD-2, MOD);
    for (int i = MAXN-2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
    }
}

long long binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    return (fact[n] * inv_fact[k] % MOD) * inv_fact[n-k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        long long answer = 0;
        
        // For each i from 1 to n, compute f(i)
        for (int i = 1; i <= n; i++) {
            long long f_i = 0;
            // f(i) = C(i,i) XOR C(i+1,i) XOR ... XOR C(n,i)
            for (int j = i; j <= n; j++) {
                f_i ^= binomial(j, i);
            }
            answer ^= f_i;
        }
        
        cout << answer << "\n";
    }
    
    return 0;
}
