#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>
#include <iomanip>

using namespace std;

// Structure to store topping information
struct Topping {
    double angle;
    long long value;
};

// Function to calculate the maximum subarray sum within angular and size limits
// This uses a Monotonic Queue (Deque) optimization
long long get_max_subarray(int n, double theta_max, const vector<Topping>& toppings) {
    int m = toppings.size(); // This is 2*n
    vector<long long> prefix(m + 1, 0);
    
    // Compute prefix sums
    for (int i = 0; i < m; ++i) {
        prefix[i + 1] = prefix[i] + toppings[i].value;
    }

    long long max_val = 0;
    deque<int> dq;
    
    // We iterate through 'i' which represents the END of the slice (0-based index in toppings)
    // The slice is toppings[start...i].
    // The sum is prefix[i+1] - prefix[start].
    // We need to minimize prefix[start].
    // 'start' corresponds to an index 'k' in the prefix array such that:
    // 1. angular difference is valid
    // 2. length is at most n
    
    int left_bound_ptr = 0;
    
    // Initialize deque with index 0 (representing an empty prefix before the first element)
    // dq stores indices 'k' of the prefix array
    dq.push_back(0); 
    
    for (int i = 0; i < m; ++i) {
        // Current slice ends at topping 'i'
        
        // 1. Update the angular left bound
        // We need toppings[i].angle - toppings[left_bound_ptr].angle <= theta_max
        while (left_bound_ptr <= i && (toppings[i].angle - toppings[left_bound_ptr].angle > theta_max + 1e-9)) {
            left_bound_ptr++;
        }
        
        // 2. Determine the valid range for the subtraction index 'k'
        // The slice is from some index 's' to 'i'.
        // 's' must be >= left_bound_ptr
        // 's' must be >= i - n + 1 (cannot take more than n items)
        // The prefix index 'k' corresponds to 's', so k = s.
        // Thus k must be >= max(left_bound_ptr, i - n + 1)
        
        int min_valid_k = max(left_bound_ptr, i - n + 1);
        
        // Remove indices from the front of the deque that are no longer valid
        // The index in deque refers to the index in the prefix array (0 to m)
        // Wait, prefix[k] means sum of first k elements. 
        // If we subtract prefix[k], the slice starts at toppings[k].
        // So if valid slice starts at index 's' (0-based index in toppings), 
        // we subtract prefix[s].
        // So we need indices in deque >= min_valid_k.
        
        while (!dq.empty() && dq.front() < min_valid_k) {
            dq.pop_front();
        }
        
        // If deque is valid, update answer
        if (!dq.empty()) {
            max_val = max(max_val, prefix[i + 1] - prefix[dq.front()]);
        }
        
        // Add current prefix index (i + 1) to deque for future iterations
        // Maintain monotonic increasing order (since we want to subtract the MINIMUM prefix)
        while (!dq.empty() && prefix[dq.back()] >= prefix[i + 1]) {
            dq.pop_back();
        }
        dq.push_back(i + 1);
    }
    
    return max_val;
}

void solve() {
    int n;
    long long r_in, A_in;
    cin >> n >> r_in >> A_in;
    
    double r = (double)r_in;
    double A = (double)A_in;
    
    vector<Topping> points(n);
    for (int i = 0; i < n; ++i) {
        long long x, y, v;
        cin >> x >> y >> v;
        // Calculate angle in range (-PI, PI]
        points[i] = {atan2((double)y, (double)x), v};
    }
    
    // Sort by angle
    sort(points.begin(), points.end(), [](const Topping& a, const Topping& b) {
        return a.angle < b.angle;
    });
    
    // Duplicate points to handle circular wrap-around
    const double PI = acos(-1.0);
    for (int i = 0; i < n; ++i) {
        points.push_back({points[i].angle + 2 * PI, points[i].value});
    }
    
    // Calculate max allowed angle
    // Area = 0.5 * r^2 * theta  =>  theta = 2 * Area / r^2
    double theta_max = (2.0 * A) / (r * r);
    
    // Case 1: Maximize positive sum (find max subarray sum)
    long long ans1 = get_max_subarray(n, theta_max, points);
    
    // Case 2: Maximize negative sum (find max subarray sum with negated values)
    // This is equivalent to minimizing sum and taking absolute value
    vector<Topping> negated_points = points;
    for (int i = 0; i < negated_points.size(); ++i) {
        negated_points[i].value = -negated_points[i].value;
    }
    long long ans2 = get_max_subarray(n, theta_max, negated_points);
    
    cout << max(ans1, ans2) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}