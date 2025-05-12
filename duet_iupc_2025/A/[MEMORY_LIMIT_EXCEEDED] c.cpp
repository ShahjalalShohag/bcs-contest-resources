#include <iostream>
#include <vector>
#include <map>
#include <tuple>   // Required for storing coordinates
#include <cstdio>
// #include <utility> // No longer needed for pair

using namespace std;

int MOD = 998244353;
// Define dimensions based on maximum possible values + buffer
const int MAX_N_DIM = 405;   // Max n + buffer (for score and rem dimensions)
const int MAX_LEN_DIM = 205; // Max len (2*n) + buffer (for open dimension)


int n;      // Number of pairs from input
int len;    // Total steps (2*n)

// Memoization table: Array indexed by [score][open][rem].
// The map at each index stores results (int) keyed by 'i' (step number).
map<int, int> memo[MAX_N_DIM][MAX_N_DIM][MAX_N_DIM];

// Stores coordinates (score, open, rem, i) of states whose results were computed and stored in 'memo'
// during the *current* test case. Will be cleared before the next test case.
vector<tuple<int, int, int, int>> used_memo_cells;

// Recursive function with memoization
// Calculates the sum of (final_score * number_of_ways) starting from state (i, score, open, rem)
int solve(int i, int score, int open, int rem) {
    // Base Case: Reached the end of the process (len steps)
    if (i == len) {
        return (open == 0 && rem == 0) ? score : 0;
    }

    // --- Memoization Check ---
    // Check if a result exists for state (i, score, open, rem)
    // We don't need the test case ID check anymore.
    if (memo[score][open][rem].count(i)) {
        return memo[score][open][rem][i]; // Return cached result
    }

    // Initialize the total score sum for paths starting from this state
    long long total_score_sum = 0;

    // --- Transitions based on the next action at step 'i' ---

    // Option 1: Close one of the 'open' items.
    if (open >= 1) {
        total_score_sum = (total_score_sum + 1LL * open * solve(i + 1, score + 1, 0, rem)) % MOD;
    }

    // Option 2: Open one of the 'rem' remaining items.
    if (rem >= 1) {
        total_score_sum = (total_score_sum + 1LL * rem * solve(i + 1, score, open + 1, rem - 1)) % MOD;
    }

    // Option 3: Process a "neutral" item.
    int not_affect = len - i - 2 * rem - open;
    if (not_affect >= 1) {
        total_score_sum = (total_score_sum + 1LL * not_affect * solve(i + 1, score, open, rem)) % MOD;
    }

    // --- Store Result ---
    // Convert result to int after modulo.
    int result_int = (int)total_score_sum;
    // Store the computed result in the map.
    memo[score][open][rem][i] = result_int;

    // *** Track that this memoization cell was used ***
    // Store the coordinates (s, o, r, i) so we can clear this entry later.
    used_memo_cells.emplace_back(score, open, rem, i);

    return result_int;
}

int main() {
    // Optional: Faster I/O operations
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    // Use cin if using faster I/O
    // scanf("%d", &t);
    cin >> t;
    while (t--) {
        // *** Clear only the memoization cells used in the PREVIOUS test case ***
        // Iterate through the coordinates recorded during the last run.
        for (const auto& state_coords : used_memo_cells) {
            int s, o, r, i_key;
            // Unpack the coordinates
            tie(s, o, r, i_key) = state_coords;
            // Access the specific map and erase the entry for the step 'i_key'.
            // Basic bounds check for safety, though correct logic shouldn't exceed them.
             if (s < MAX_N_DIM && o < MAX_LEN_DIM && r < MAX_N_DIM) {
                 // map::erase(key) removes the element with the given key if it exists.
                 // It does nothing if the key is not found.
                 memo[s][o][r].erase(i_key);
             }
        }
        // Clear the tracking vector itself to prepare for the current test case.
        used_memo_cells.clear();
        // Optional: If memory usage is a concern for very large numbers of states,
        // you might consider shrinking the vector's capacity.
        // used_memo_cells.shrink_to_fit();


        // scanf("%d", &n);
        cin >> n >> MOD;
        len = 2 * n; // Calculate total steps

        // Start the recursion from the initial state: step 0, score 0, open 0, rem n.
        int ans = solve(0, 0, 0, n);

        // Use cout if using faster I/O
        // printf("%d\n", ans);
        cout << ans << "\n";
    }

    return 0;
}