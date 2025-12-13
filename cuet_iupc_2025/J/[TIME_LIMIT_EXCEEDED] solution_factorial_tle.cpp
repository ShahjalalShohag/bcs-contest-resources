/**
 * Problem: factorial-shohag
 * Solution using: Fenwick Tree (BIT) + std::set + Naive Dynamic Calculation
 * Complexity: O(Sum(Values)) in worst case -> TLE expected, but logic is correct (No WA)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005; 
const int very_big = -1;

int fact[MAX_N];

int n, q;
int bit[MAX_N];
int cur_val[MAX_N];
int cur_seed[MAX_N];
set<int> active_indices;

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        // Cast to long long just for the multiplication to prevent overflow
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
}

void update(int idx, int val)
{
    // Handle negative results from differences
    if (val < 0) val += MOD;
    
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
        if (bit[idx] >= MOD) bit[idx] -= MOD;
    }
}

int query(int idx)
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
    int res = query(r) - query(l - 1);
    if (res < 0) res += MOD;
    return res;
}

void solve()
{
    cin >> n >> q;

    // Efficiently clear BIT for the current N
    for (int i = 0; i <= n; ++i) bit[i] = 0;
    
    active_indices.clear();

    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;

        cur_val[i] = val;
        cur_seed[i] = val;

        update(i, val);

        // 1 and 2 are stable (1! = 1, 2! = 2). 
        // 0 becomes 1 (active). >= 3 changes (active).
        if (val == 0 || val >= 3)
            active_indices.insert(i);
    }

    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
        {
            auto it = active_indices.lower_bound(l);

            while (it != active_indices.end() && *it <= r)
            {
                int idx = *it;
                int seed = cur_seed[idx];

                int new_seed;
                int new_val;
                bool remove = false;

                if (seed == very_big)
                {
                    // Case: Number was huge (>= 13!). Next factorial is 0 mod M.
                    new_seed = very_big;
                    new_val = 0;
                    remove = true;
                }
                else if (seed > 12)
                {
                    // Case: Seed is large (e.g. 13, or 10!, 11!, 12!)
                    // We need to calculate seed! % MOD.
                    
                    if (seed < MAX_N) {
                        // Precomputed range
                        new_val = fact[seed];
                    } 
                    else {
                        // Naive Computation: Calculate factorial from MAX_N up to seed.
                        // For seed = 12! (479,001,600), this loop runs ~4.78*10^8 times.
                        // This ensures mathematical correctness (No WA) but is slow (TLE).
                        long long val = fact[MAX_N - 1];
                        for (int k = MAX_N; k <= seed; k++) {
                            val = (val * k) % MOD;
                        }
                        new_val = (int)val;
                    }

                    // Since seed > 12, seed! is physically huge (> MOD)
                    // The next state is very_big (Sentinel)
                    new_seed = very_big;
                }
                else
                {
                    // Small seed <= 12
                    int f = fact[seed];
                    new_seed = f;
                    new_val = f;

                    if (new_seed == 1 || new_seed == 2)
                        remove = true;
                }

                // Calculate difference for BIT update
                int diff = new_val - cur_val[idx];
                update(idx, diff);

                cur_val[idx] = new_val;
                cur_seed[idx] = new_seed;

                if (remove)
                    it = active_indices.erase(it);
                else
                    ++it;
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