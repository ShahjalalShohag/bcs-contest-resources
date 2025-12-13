/**
 * Problem: factorial-shohag
 * Solution using: Fenwick Tree (BIT) + DSU (Optimization for skipping) + Dynamic Factorial Extension
 * Complexity: O((N + Q) * alpha(N) + M)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005; 
const int very_big = -1;

int fact[MAX_N];
int n, q;
long long bit[MAX_N]; // Using long long for BIT safety
int cur_val[MAX_N];
int cur_seed[MAX_N];

// DSU Array for efficient skipping of stable indices
int parent[MAX_N];

// Special seed values (calculated in precompute)
int S10, S11, S12;

// Cache for extending factorial beyond MAX_N
int max_computed_n; 
int max_computed_val; 

// Explicit cache variables instead of map
int cached_S10 = 0;
int cached_S11 = 0;
int cached_S12 = 0;

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    
    // 10!, 11!, 12! fit in int and are < MOD
    S10 = fact[10];
    S11 = fact[11];
    S12 = fact[12];
        
    // Initialize the extender pointer
    max_computed_n = MAX_N - 1;
    max_computed_val = fact[MAX_N - 1];
}

// DSU Find with Path Compression
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

// Calculate factorials larger than MAX_N on demand
int get_extended_factorial(int target_n) {
    if (target_n >= MOD) return 0;
    
    // If we've already computed past this, return the cached values.
    // This assumes target_n is one of S10, S11, S12.
    if (target_n <= max_computed_n) {
        if (target_n == S10 && cached_S10 != 0) return cached_S10;
        if (target_n == S11 && cached_S11 != 0) return cached_S11;
        if (target_n == S12 && cached_S12 != 0) return cached_S12;
        // If not one of these, or not cached yet (should not happen with correct logic), proceed.
    }

    long long cur = max_computed_val;
    
    // We start from the last computed point and move up
    // Note: If target_n < max_computed_n, loop condition false, cur remains max_computed_val.
    // This is why the explicit check above is critical for S10/S11 requests after S12.
    for (int i = max_computed_n + 1; i <= target_n; i++) {
        cur = (cur * i) % MOD;
        
        // Opportunistic Caching: Capture values as we pass them
        if (i == S10) cached_S10 = cur;
        else if (i == S11) cached_S11 = cur;
        else if (i == S12) cached_S12 = cur;
    }
    
    // Update global frontier only if we advanced
    if (target_n > max_computed_n) {
        max_computed_n = target_n;
        max_computed_val = cur;
    }
    
    return cur;
}

int get_large_fact_safe(int seed) {
    // Fast return if cached
    if (seed == S10 && cached_S10 != 0) return cached_S10;
    if (seed == S11 && cached_S11 != 0) return cached_S11;
    if (seed == S12 && cached_S12 != 0) return cached_S12;
    
    return get_extended_factorial(seed);
}

void update_bit(int idx, int val)
{
    if (val < 0) val += MOD;
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
        if (bit[idx] >= MOD) bit[idx] -= MOD;
    }
}

int query_bit(int idx)
{
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
        if (sum >= MOD) sum -= MOD;
    }
    return sum;
}

int query_range(int l, int r)
{
    int res = query_bit(r) - query_bit(l - 1);
    if (res < 0) res += MOD;
    return res;
}

void solve()
{
    cin >> n >> q;

    // Reset data structures for current test case
    for (int i = 0; i <= n + 1; ++i) {
        bit[i] = 0;
        parent[i] = i; // Initialize DSU
    }

    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;

        cur_val[i] = val;
        cur_seed[i] = val;

        update_bit(i, val);

        // 1 and 2 are stable (1! = 1, 2! = 2). 
        // 0 is active (0! = 1), then becomes stable.
        if (val == 1 || val == 2) {
            parent[i] = i + 1; // Mark as stable immediately
        }
    }

    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
        {
            // Iterate using DSU to skip stable elements
            // Note: idx can jump to n+1, so condition idx <= r is sufficient
            for (int idx = find_set(l); idx <= r; idx = find_set(idx + 1))
            {
                int seed = cur_seed[idx];
                int new_seed;
                int new_val;
                bool become_stable = false;

                if (seed == very_big)
                {
                    // Transition: (Huge)! -> 0 mod M
                    new_seed = very_big;
                    new_val = 0;
                    become_stable = true; // 0 is stable
                }
                else if (seed == S10 || seed == S11 || seed == S12)
                {
                    // Transition: 10! -> (10!)! mod M
                    new_val = get_large_fact_safe(seed);
                    new_seed = very_big;
                }
                else if (seed > 12)
                {
                    // Transition: 13 -> 13! (Huge, > M)
                    // We store fact[13] % M as value, but seed is marked Huge
                    if (seed < MAX_N) new_val = fact[seed];
                    else new_val = 0; // Should not happen with inputs <= 10^6
                    
                    new_seed = very_big;
                }
                else
                {
                    // Small seed <= 12
                    int f = fact[seed];
                    new_seed = f;
                    new_val = f;

                    if (new_seed == 1 || new_seed == 2)
                        become_stable = true;
                }

                int diff = new_val - cur_val[idx];
                update_bit(idx, diff);

                cur_val[idx] = new_val;
                cur_seed[idx] = new_seed;

                if (become_stable) {
                    parent[idx] = find_set(idx + 1);
                }
            }
        }
        else
        {
            cout << query_range(l, r) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    if (cin >> t)
    {
        while (t--)
            solve();
    }
    return 0;
}