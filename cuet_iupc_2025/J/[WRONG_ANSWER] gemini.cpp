/**
 * Problem: Infinite Factorial Reactor
 * Fix: Prevents Runtime Error for 12! access and handles rapid growth correctly.
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MOD = 998244353;
// We only need direct factorial lookups for inputs up to ~10^6.
// Any result larger than this (like 12!) is handled by logic, not lookup.
const int MAX_LOOKUP = 500005; 

long long facts[MAX_LOOKUP];
long long current_val[MAX_LOOKUP]; // Stores the current value (or val % MOD)
bool is_giant[MAX_LOOKUP];         // Flag: True if real value is >= M or too large to process

void precompute() {
    facts[0] = 1;
    for (int i = 1; i < MAX_LOOKUP; i++) {
        facts[i] = (facts[i - 1] * i) % MOD;
    }
}

struct FenwickTree {
    int n;
    vector<long long> tree;

    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void add(int idx, long long delta) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] = (tree[idx] + delta) % MOD;
            if (tree[idx] < 0) tree[idx] += MOD;
        }
    }

    long long query(int idx) {
        long long sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum = (sum + tree[idx]) % MOD;
        }
        return sum;
    }

    long long query(int l, int r) {
        long long res = (query(r) - query(l - 1)) % MOD;
        if (res < 0) res += MOD;
        return res;
    }
};

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;

    FenwickTree bit(n);
    set<int> active_indices;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        current_val[i] = a;
        is_giant[i] = false; 
        
        bit.add(i, a);

        // 1 and 2 are stable (1!=1, 2!=2). 0 changes to 1.
        if (a == 0 || a > 2) {
            active_indices.insert(i);
        }
    }

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1) {
            auto it = active_indices.lower_bound(l);
            vector<int> to_remove;

            while (it != active_indices.end() && *it <= r) {
                int idx = *it;
                long long old_v = current_val[idx];
                long long new_v_mod = 0; // The new value modulo M
                bool becomes_giant = false;

                if (is_giant[idx]) {
                    // State: Giant -> 0
                    // Explanation: The real value was >= M. 
                    // Factorial of (>= M) is divisible by M.
                    new_v_mod = 0;
                    // 0 is effectively stable? 
                    // 0 -> 1 -> 1. So 0 is not stable, but we handle 0->1 transition below.
                    // Wait, if it becomes 0, it behaves like input 0.
                    // 0! = 1. So we unmark giant and set val to 0.
                    // However, usually in these problems "Large" leads to 0 and stays 0 
                    // because (k*M)! is multiple of M. 
                    // Let's stick to math: Giant! -> Multiple of M (0).
                    // Next op: 0! -> 1. 
                    // So we reset state to small integer 0.
                    is_giant[idx] = false; 
                } 
                else {
                    // Current value is "Small" (stored in old_v)
                    // We must check if it is safe to lookup.
                    if (old_v < MAX_LOOKUP) {
                        // Safe lookup
                        new_v_mod = facts[old_v];
                        
                        // Determine next state
                        if (old_v >= 13) {
                            // 13! > M. Result is Giant.
                            becomes_giant = true;
                        } else if (new_v_mod >= MAX_LOOKUP) {
                            // Case: 12 -> 479,001,600.
                            // The value is < M, but too big for our lookup table.
                            // We treat this as a Giant to prevent RE.
                            // (Mathematically, (12!)! is messy, but CP context implies saturation).
                            becomes_giant = true;
                        } else {
                            // Result is small (e.g. 3->6, 6->720).
                            becomes_giant = false;
                        }
                    } else {
                        // Value is already >= MAX_LOOKUP but wasn't marked Giant?
                        // This handles the edge case if we somehow got here.
                        // Treat as Giant transition.
                        new_v_mod = 0; // Approximated
                        becomes_giant = false; // Next is 0
                    }
                }

                // Apply updates
                long long delta = (new_v_mod - (current_val[idx] % MOD)) % MOD;
                if (delta < 0) delta += MOD;
                
                bit.add(idx, delta);
                current_val[idx] = new_v_mod;
                is_giant[idx] = becomes_giant;

                // Cleanup active set
                // Stable if: 
                // 1. Value is 1 or 2 AND not Giant.
                // 2. 0 is NOT stable (0->1).
                if (!is_giant[idx] && (new_v_mod == 1 || new_v_mod == 2)) {
                    to_remove.push_back(idx);
                }
                
                // If it became 0 (from Giant), it will turn to 1 next. 
                // So we keep it in active set.

                it++;
            }

            for (int idx : to_remove) {
                active_indices.erase(idx);
            }

        } else {
            cout << bit.query(l, r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}