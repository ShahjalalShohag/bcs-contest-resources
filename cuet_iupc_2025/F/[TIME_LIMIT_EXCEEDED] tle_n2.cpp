#include <iostream>
#include <vector>
#include <cmath> // For abs

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
    
    long long sum_abs_diff = 0;
    
    // Brute force O(N^2): Iterate over all unique pairs (i, j)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long diff = abs(a[i] - a[j]);
            sum_abs_diff = (sum_abs_diff + (diff % MOD)) % MOD;
        }
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