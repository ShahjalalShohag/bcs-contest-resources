/**
 * Problem: factorial-shohag
 * Solution using: Naive Segment Tree (NO Beats Optimization)
 * Complexity: O(N * Q) - This is slow and likely to TLE
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
    // 'active' flag REMOVED: We no longer prune updates
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
}

void build(int node, int start, int end, const vector<int>& a)
{
    if (start == end)
    {
        int val = a[start];
        tree[node].sum = val; 
        tree[node].seed = val;
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid, a);
    build(2 * node + 1, mid + 1, end, a);
    push_up(node);
}

void update(int node, int start, int end, int l, int r)
{
    // Standard out-of-range check
    if (start > end || start > r || end < l)
        return;

    // PRUNING REMOVED: We recurse even if the range is already stable (1s, 2s, 0s)

    if (start == end)
    {
        int seed = tree[node].seed;
        int new_seed;
        int new_val;

        if (seed == very_big)
        {
            new_seed = very_big;
            new_val = 0;
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
            if (seed < MAX_N) new_val = fact[seed];
            else new_val = 0; 
            
            new_seed = very_big;
        }
        else
        {
            // Small seed <= 12
            int f = fact[seed];
            new_seed = f;
            new_val = f;
        }

        tree[node].seed = new_seed;
        tree[node].sum = new_val;
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