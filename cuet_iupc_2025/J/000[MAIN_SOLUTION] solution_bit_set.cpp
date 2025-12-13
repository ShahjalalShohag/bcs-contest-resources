/**
 * Problem: factorial-shohag
 * Solution using: Fenwick Tree (BIT) + std::set + Hardcoded Special Values
 * Complexity: O((N + Q) * log N + M)
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAX_PRECOMPUTE = 500005;
const int very_big = -1;

const long long S10 = 3628800;
const long long S11 = 39916800;
const long long S12 = 479001600;

long long fact[MAX_PRECOMPUTE];

int n, q;
vector<long long> bit;
vector<long long> cur_val;
vector<long long> cur_seed;
set<int> active_indices;

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAX_PRECOMPUTE; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
}

void update(int idx, long long val)
{
    val %= MOD;
    if (val < 0)
        val += MOD;

    for (; idx <= n; idx += idx & -idx)
        bit[idx] = (bit[idx] + val) % MOD;
}

long long query(int idx)
{
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum = (sum + bit[idx]) % MOD;
    return sum;
}

long long query_range(int l, int r)
{
    return (query(r) - query(l - 1) + MOD) % MOD;
}

void solve()
{
    cin >> n >> q;

    bit.assign(n + 1, 0);
    cur_val.assign(n + 1, 0);
    cur_seed.assign(n + 1, 0);
    active_indices.clear();

    for (int i = 1; i <= n; i++)
    {
        long long val;
        cin >> val;

        cur_val[i] = val;
        cur_seed[i] = val;

        update(i, val);

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
                long long seed = cur_seed[idx];

                long long new_seed;
                long long new_val;
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

                    new_val = fact[seed];
                    new_seed = very_big;
                }
                else
                {
                    long long f = fact[seed];
                    new_seed = f;
                    new_val = f;

                    if (new_seed == 1 || new_seed == 2)
                        remove = true;
                }

                long long diff = new_val - cur_val[idx];
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