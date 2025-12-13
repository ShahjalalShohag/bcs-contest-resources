/**
 * Problem: factorial-shohag
 * Solution using: Segment Tree (Beats Optimization) + Optimized Ints
 * Complexity: O((N + Q) * log N + M)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005; 
const int very_big = -1;

// Special seeds (all fit in 32-bit int)
const int S10 = 3628800;
const int S11 = 39916800;
const int S12 = 479001600;

int fact[MAX_N];

struct Node {
    int sum;
    int seed; // Stores the value for leaf nodes used to calculate next state
    bool active;    // True if range contains values that can change (>=3 or 0)
} tree[4 * MAX_N];

int n, q;

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        // Cast to long long for multiplication to avoid overflow before modulo
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
}

void push_up(int node)
{
    // Optimized modular addition
    int val = tree[2 * node].sum + tree[2 * node + 1].sum;
    if (val >= MOD) val -= MOD;
    tree[node].sum = val;
    
    tree[node].active = tree[2 * node].active || tree[2 * node + 1].active;
}

void build(int node, int start, int end, const vector<int>& a)
{
    if (start == end)
    {
        int val = a[start];
        tree[node].sum = val; // Inputs are guaranteed <= 10^6 < MOD
        tree[node].seed = val;
        // Active if it can change: 0 changes to 1. >=3 changes.
        // 1 and 2 are stable.
        tree[node].active = (val == 0 || val >= 3);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid, a);
    build(2 * node + 1, mid + 1, end, a);
    push_up(node);
}

void update(int node, int start, int end, int l, int r)
{
    // If out of range or fully inactive, stop.
    if (start > end || start > r || end < l || !tree[node].active)
        return;

    if (start == end)
    {
        int seed = tree[node].seed;
        int new_seed;
        int new_val;
        bool still_active = true;

        if (seed == very_big)
        {
            new_seed = very_big;
            new_val = 0;
            still_active = false; // 0 (from huge) is stable
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
            // Initial input > 12. 
            // Result is fact[seed] % MOD (if within range), but physically > MOD.
            if (seed < MAX_N) new_val = fact[seed];
            else new_val = 0; // Should not happen with N <= 10^6
            
            new_seed = very_big;
        }
        else
        {
            // Small seed <= 12
            int f = fact[seed];
            new_seed = f;
            new_val = f;
            
            // 1 and 2 are stable
            if (new_seed == 1 || new_seed == 2)
                still_active = false;
        }

        tree[node].seed = new_seed;
        tree[node].sum = new_val; // All new_val sources are already modulo-safe
        tree[node].active = still_active;
        return;
    }

    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    push_up(node);
}

int query(int node, int start, int end, int l, int r)
{
    if (start > end || start > r || end < l)
        return 0;
    
    if (l <= start && end <= r)
        return tree[node].sum;

    int mid = (start + end) / 2;
    
    // Optimized modular addition
    int res = query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    if (res >= MOD) res -= MOD;
    return res;
}

void solve()
{
    if (!(cin >> n >> q)) return;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    build(1, 1, n, a);

    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1)
        {
            update(1, 1, n, l, r);
        }
        else
        {
            cout << query(1, 1, n, l, r) << "\n";
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