#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;

// Function to calculate (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Function to calculate modular inverse using Fermat's Little Theorem
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // Sort the array to efficiently calculate sum of absolute differences
    sort(a.begin(), a.end());
    
    long long sum_abs_diff = 0;
    
    for (int i = 0; i < n; ++i) {
        // Calculate the coefficient for a[i]
        // a[i] is added for 'i' pairs (where it is larger)
        // a[i] is subtracted for 'n - 1 - i' pairs (where it is smaller)
        // Net coefficient = i - (n - 1 - i) = 2*i - n + 1
        long long coeff = (2LL * i - n + 1);
        
        // Handle modulo for potentially negative numbers/coefficients
        long long val_mod = (a[i] % MOD + MOD) % MOD;
        long long coeff_mod = (coeff % MOD + MOD) % MOD;
        
        long long term = (val_mod * coeff_mod) % MOD;
        sum_abs_diff = (sum_abs_diff + term) % MOD;
    }
    
    // The expected value is (Sum of Differences) * (2 / n)
    long long ans = (sum_abs_diff * 2) % MOD;
    ans = (ans * modInverse(n)) % MOD;
    
    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}