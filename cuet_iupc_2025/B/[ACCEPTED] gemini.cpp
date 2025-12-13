#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

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

// Function to calculate modular inverse
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void solve() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return;

    // Read input and count frequencies
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        cnt[val]++;
    }

    // Collect distinct values > 1 for DP transitions
    // This helps in iterating only relevant transitions
    vector<int> vals;
    vals.reserve(n);
    for (int i = 2; i <= n; ++i) {
        if (cnt[i] > 0) vals.push_back(i);
    }
    // vals is naturally sorted because we iterated from 2 to n

    // Precompute Prefix Sums of counts to calculate G[v] efficiently
    vector<int> pref(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + cnt[i];
    }
    pref[n+1] = pref[n]; // Safety boundary

    // G[v] = sum_{x in a} floor(x / v)
    // We compute this using the harmonic property: floor(x/v) is constant for blocks of x
    vector<long long> G(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        for (int j = 1; j * v <= n; ++j) {
            // range of x where floor(x/v) == j is [j*v, (j+1)*v - 1]
            int lower = j * v;
            int upper = min(n, (j + 1) * v - 1);
            int count_in_range = pref[upper] - pref[lower - 1];
            if (count_in_range > 0) {
                G[v] = (G[v] + (long long)j * count_in_range) % MOD;
            }
        }
    }

    // dp[p] stores the number of sequences of length 'm' (current iteration)
    // consisting of elements > 1 such that their product is 'p'.
    vector<long long> dp(n + 1, 0);
    dp[1] = 1; // Base case: product 1 with 0 elements > 1

    long long ans = 0;
    long long binom = 1; // Stores C(k-1, m)
    int c1 = cnt[1];
    
    // We iterate m: number of elements > 1 in the divisor sequence.
    // If product exceeds n, the floor becomes 0. 
    // Since smallest element > 1 is 2, and 2^20 > 10^6, we stop around 20.
    int limit = 22; 

    for (int m = 0; m <= limit; ++m) {
        // If we need more non-1 elements than available positions (k-1), stop.
        if (m > k - 1) break;

        // Calculate contribution for this specific m
        // Formula: C(k-1, m) * c1^(k-1-m) * sum(dp[p] * G[p])
        
        long long ways_to_fill_ones = power(c1, k - 1 - m);
        long long ways_seq = (binom * ways_to_fill_ones) % MOD;
        
        long long sum_dp_G = 0;
        bool any_dp = false;

        for (int p = 1; p <= n; ++p) {
            if (dp[p] > 0) {
                sum_dp_G = (sum_dp_G + dp[p] * G[p]) % MOD;
                any_dp = true;
            }
        }

        ans = (ans + ways_seq * sum_dp_G) % MOD;
        
        // If no products <= n exist, higher m will also be 0
        if (!any_dp) break;

        // Update Binomial Coefficient for next iteration: C(N, m) -> C(N, m+1)
        // C(N, m+1) = C(N, m) * (N - m) / (m + 1)
        // Here N = k - 1
        if (m < limit && m < k - 1) {
             long long num = (k - 1 - m) % MOD;
             long long den = modInverse(m + 1);
             binom = (binom * num) % MOD;
             binom = (binom * den) % MOD;
        }

        // DP Transition: Compute dp array for sequences of length m+1
        vector<long long> next_dp(n + 1, 0);
        
        // Iterate current products 'p' and extend with values 'v' from vals
        for (int p = 1; p <= n; ++p) {
            if (dp[p] == 0) continue;
            long long cur_count = dp[p];
            
            for (int v : vals) {
                // If product exceeds n, we can stop (vals is sorted)
                if ((long long)p * v > n) break;
                
                int target = p * v;
                long long added_ways = (cur_count * cnt[v]) % MOD;
                
                next_dp[target] += added_ways;
                if (next_dp[target] >= MOD) next_dp[target] -= MOD;
            }
        }
        dp = move(next_dp);
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}