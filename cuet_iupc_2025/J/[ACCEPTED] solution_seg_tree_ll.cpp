/**
 * Problem: factorial-shohag
 * Solution using: Segment Tree (Beats Optimization)
 * Complexity: O((N + Q) * log N + M)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_N = 500005; 
const long long very_big = -1;

// Special seeds
const long long S10 = 3628800;
const long long S11 = 39916800;
const long long S12 = 479001600;

long long fact[MAX_N];

struct Node {
    long long sum;
    long long seed; // Stores the value for leaf nodes used to calculate next state
    bool active;    // True if range contains values that can change (>=3 or 0)
} tree[4 * MAX_N];

int n, q;

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
}

void push_up(int node)
{
    tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
    tree[node].active = tree[2 * node].active || tree[2 * node + 1].active;
}

void build(int node, int start, int end, const vector<long long>& a)
{
    if (start == end)
    {
        long long val = a[start];
        tree[node].sum = val % MOD;
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
        long long seed = tree[node].seed;
        long long new_seed;
        long long new_val;
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
            long long f = fact[seed];
            new_seed = f;
            new_val = f;
            
            // 1 and 2 are stable
            if (new_seed == 1 || new_seed == 2)
                still_active = false;
        }

        tree[node].seed = new_seed;
        tree[node].sum = new_val % MOD;
        tree[node].active = still_active;
        return;
    }

    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    push_up(node);
}

long long query(int node, int start, int end, int l, int r)
{
    if (start > end || start > r || end < l)
        return 0;
    
    if (l <= start && end <= r)
        return tree[node].sum;

    int mid = (start + end) / 2;
    return (query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r)) % MOD;
}

void solve()
{
    cin >> n >> q;

    vector<long long> a(n + 1);
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
    cin >> t;
    while(t--)
        solve();
    return 0;
}