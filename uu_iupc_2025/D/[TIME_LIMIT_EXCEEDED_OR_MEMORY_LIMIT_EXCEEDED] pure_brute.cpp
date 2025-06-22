#include <bits/stdc++.h>
using namespace std;

// Function to perform prefix-suffix swap operation
vector<int> swap_prefix_suffix(const vector<int>& arr, int len) {
    int n = arr.size();
    if (len <= 0 || len > n/2) return arr; // Invalid operation
    
    vector<int> result = arr;
    // Swap prefix of length len with suffix of length len
    for (int i = 0; i < len; i++) {
        swap(result[i], result[n - len + i]);
    }
    return result;
}

// Function to generate the i-th left cyclic shift of array c
// f(c, i) = [c_{i+1}, c_{i+2}, ..., c_n, c_1, c_2, ..., c_i]
vector<int> cyclic_shift(const vector<int>& c, int i) {
    int n = c.size();
    vector<int> result(n);
    for (int j = 0; j < n; j++) {
        result[j] = c[(i + j) % n];
    }
    return result;
}

// Function to check if target array is reachable from start array
bool is_reachable(const vector<int>& start, const vector<int>& target) {
    int n = start.size();
    if (n != target.size()) return false;
    if (start == target) return true;
    
    // Quick check: both arrays must have same multiset of elements
    vector<int> start_sorted = start, target_sorted = target;
    sort(start_sorted.begin(), start_sorted.end());
    sort(target_sorted.begin(), target_sorted.end());
    if (start_sorted != target_sorted) return false;
    
    // BFS to explore all reachable states
    queue<vector<int>> q;
    set<vector<int>> visited;
    
    q.push(start);
    visited.insert(start);
    
    int max_prefix_len = n / 2;
    
    while (!q.empty()) {
        vector<int> current = q.front();
        q.pop();
        
        if (current == target) return true;
        
        // Try all possible prefix-suffix swaps
        for (int len = 1; len <= max_prefix_len; len++) {
            vector<int> next = swap_prefix_suffix(current, len);
            
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        
        int count = 0;
        
        // Check all pairs (i, j) where 0 <= i, j < n
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                vector<int> f_a_i = cyclic_shift(a, i);
                vector<int> f_b_j = cyclic_shift(b, j);
                
                if (is_reachable(f_a_i, f_b_j)) {
                    count++;
                }
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
