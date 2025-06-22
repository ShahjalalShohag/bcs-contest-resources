#include <bits/stdc++.h>
using namespace std;

// Function to compute the canonical form (sorted symmetric pairs + middle element)
// for a given array that represents the equivalence class under prefix-suffix swaps
pair<vector<pair<int,int>>, int> get_canonical_form(const vector<int>& arr) {
    int n = arr.size();
    int N = n / 2;
    
    // Get middle element (if n is odd)
    int middle = (n % 2 == 1) ? arr[n/2] : -1;
    
    // Build multiset of unordered symmetric pairs
    vector<pair<int,int>> pairs;
    pairs.reserve(N);
    
    for (int j = 0; j < N; j++) {
        int x = arr[j], y = arr[n-1-j];
        if (x > y) swap(x, y);
        pairs.emplace_back(x, y);
    }
    
    sort(pairs.begin(), pairs.end());
    return {pairs, middle};
}

// Function to generate the i-th left cyclic shift of array c
vector<int> cyclic_shift(const vector<int>& c, int i) {
    int n = c.size();
    vector<int> result(n);
    for (int j = 0; j < n; j++) {
        result[j] = c[(i + j) % n];
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        // Precompute canonical forms for all cyclic shifts of a
        vector<pair<vector<pair<int,int>>, int>> a_forms(n);
        for (int i = 0; i < n; i++) {
            vector<int> shifted_a = cyclic_shift(a, i);
            a_forms[i] = get_canonical_form(shifted_a);
        }
        
        // Precompute canonical forms for all cyclic shifts of b
        vector<pair<vector<pair<int,int>>, int>> b_forms(n);
        for (int j = 0; j < n; j++) {
            vector<int> shifted_b = cyclic_shift(b, j);
            b_forms[j] = get_canonical_form(shifted_b);
        }
        
        // Count matching pairs using a map
        map<pair<vector<pair<int,int>>, int>, int> b_count;
        for (int j = 0; j < n; j++) {
            b_count[b_forms[j]]++;
        }
        
        long long total_count = 0;
        for (int i = 0; i < n; i++) {
            total_count += b_count[a_forms[i]];
        }
        
        cout << total_count << "\n";
    }
    return 0;
}
