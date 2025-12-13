/**
 * Problem: factorial-shohag
 * Solution using: Brute Force (Standard Loops)
 * Complexity: O(N * Q)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005;
const int SENTINEL = -1; // Represents a number so large its factorial is 0 mod M

int fact[MAX_N];
int n, q;
int cur_val[MAX_N];  // Stores value % MOD (for sum queries)
int cur_seed[MAX_N]; // Stores actual value (for calculating next factorial)

// Precompute factorials up to 10^6
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    }
}

// Helper to get factorial of large numbers on the fly
int get_large_fact(int v) {
    if (v >= MOD) return 0;
    if (v < MAX_N) return fact[v];
    
    // If v >= MAX_N (e.g., 10! = 3.6M), compute manually
    long long res = fact[MAX_N - 1];
    for (int i = MAX_N; i <= v; i++) {
        res = (res * i) % MOD;
    }
    return res;
}

void solve() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> cur_seed[i];
        cur_val[i] = cur_seed[i]; // Initial values <= 10^6, so val % MOD == val
    }

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1) {
            // Brute Force Update: Iterate every index in range
            for (int i = l; i <= r; i++) {
                int s = cur_seed[i];
                
                if (s == SENTINEL) {
                    // Already huge -> (Huge)! is 0 mod M
                    cur_val[i] = 0;
                    cur_seed[i] = SENTINEL;
                }
                else if (s <= 12) {
                    // Small number: 12! fits in int
                    int f = fact[s];
                    cur_val[i] = f;
                    cur_seed[i] = f; 
                }
                else {
                    // Number > 12 (either initial > 12 or came from 10!, 11!, 12!)
                    // Its factorial will be > MOD physically, so next seed is SENTINEL
                    cur_val[i] = get_large_fact(s);
                    cur_seed[i] = SENTINEL;
                }
            }
        } 
        else {
            // Brute Force Query: Iterate and sum
            int sum = 0;
            for (int i = l; i <= r; i++) {
                sum += cur_val[i];
                if (sum >= MOD) sum -= MOD;
            }
            cout << sum << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}