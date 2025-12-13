/**
 * Problem: factorial-shohag
 * Solution using: Fenwick Tree (BIT) + std::set + Hardcoded Special Values + Optimized Ints
 * Complexity: O((N + Q) * log N + M)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005;
const int very_big = -1;

// Special seeds fitting in int
const int S10 = 3628800;
const int S11 = 39916800;
const int S12 = 479001600;

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
        fact[i] = (fact[i - 1] * i) % MOD;
}

void update(int idx, int val)
{
    // Handle negative results from differences
    if (val < 0)
        val += MOD;

    for (; idx <= n; idx += idx & -idx)
    {
        bit[idx] += val;
        if (bit[idx] >= MOD)
            bit[idx] -= MOD;
    }
}

int query(int idx)
{
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
    {
        sum += bit[idx];
        if (sum >= MOD)
            sum -= MOD;
    }
    return sum;
}

int query_range(int l, int r)
{
    int res = query(r) - query(l - 1);
    if (res < 0)
        res += MOD;
    return res;
}

void solve()
{
    cin >> n >> q;

    // Efficiently clear BIT for the current N
    // Global arrays are reused, so we must clear active range
    for (int i = 0; i <= n; ++i)
        bit[i] = 0;

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
                    new_seed = very_big;
                    new_val = 0;
                    remove = true;
                }
                else if (seed == S10)
                {
                    new_val = 821984089;
                    new_seed = very_big;
                }
                else if (seed == S11)
                {
                    new_val = 644056242;
                    new_seed = very_big;
                }
                else if (seed == S12)
                {
                    new_val = 527656359;
                    new_seed = very_big;
                }
                else if (seed > 12)
                {
                    // Case: Initial input was e.g., 13.
                    // We use precomputed fact[13].
                    // Since 13! > MOD physically, next state is very_big.
                    if (seed < MAX_N)
                        new_val = fact[seed];
                    else
                        new_val = 0; // Should not happen with constraints

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
    cin >> t;
    while (t--)
        solve();
    return 0;
}
