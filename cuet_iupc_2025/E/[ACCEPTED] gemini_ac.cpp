#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>

using namespace std;

// Structure to store topping information
struct Topping {
    double angle;
    long long value;
};

// Function to calculate the maximum subarray sum within angular and size limits
long long get_max_subarray(int max_items, double theta_max, const vector<Topping>& toppings) {
    int m = toppings.size(); 
    // Prefix sum array: prefix[i] is sum of first i elements
    vector<long long> prefix(m + 1, 0);
    
    for (int i = 0; i < m; ++i) {
        prefix[i + 1] = prefix[i] + toppings[i].value;
    }

    long long max_val = 0;
    deque<int> dq;
    
    // dq stores indices 'k' of the prefix array.
    // We want to maximize (prefix[i+1] - prefix[k])
    // This means we want to minimize prefix[k]
    
    dq.push_back(0); 
    
    int left_bound_ptr = 0;

    for (int i = 0; i < m; ++i) {
        // 1. Angular constraint: The start of the window must be within theta_max of current item
        // The slice includes items from index 'k' (exclusive) to 'i' (inclusive).
        // Actual item index for 'k' in toppings is 'k'.
        // So we need: toppings[i].angle - toppings[left_bound_ptr].angle <= theta_max
        
        while (left_bound_ptr <= i && (toppings[i].angle - toppings[left_bound_ptr].angle > theta_max + 1e-9)) {
            left_bound_ptr++;
        }
        
        // 2. Size constraint: We cannot take more items than exist in the original circle (max_items)
        // Window length is (i + 1) - k.
        // So (i + 1) - k <= max_items  =>  k >= i + 1 - max_items
        
        int min_valid_k = max(left_bound_ptr, i + 1 - max_items);
        
        // Remove indices from deque that are outside the valid window
        while (!dq.empty() && dq.front() < min_valid_k) {
            dq.pop_front();
        }
        
        // If we have a valid start point, update answer
        if (!dq.empty()) {
            max_val = max(max_val, prefix[i + 1] - prefix[dq.front()]);
        }
        
        // Maintain Monotonicity: We want smallest prefix sums at the front
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
    if (!(cin >> n >> r_in >> A_in)) return;
    
    double r = (double)r_in;
    double A = (double)A_in;
    
    vector<Topping> raw_points(n);
    for (int i = 0; i < n; ++i) {
        long long x, y, v;
        cin >> x >> y >> v;
        // atan2 returns value in (-PI, PI]
        raw_points[i] = {atan2((double)y, (double)x), v};
    }
    
    // 1. Sort by angle
    sort(raw_points.begin(), raw_points.end(), [](const Topping& a, const Topping& b) {
        return a.angle < b.angle;
    });
    
    // 2. Compress collinear points (points with same angle)
    // If we cut a slice at a specific angle, we must take ALL toppings on that radius.
    vector<Topping> distinct_points;
    if (n > 0) {
        distinct_points.push_back(raw_points[0]);
        for (int i = 1; i < n; ++i) {
            // Use epsilon for double comparison
            if (abs(raw_points[i].angle - distinct_points.back().angle) < 1e-9) {
                distinct_points.back().value += raw_points[i].value;
            } else {
                distinct_points.push_back(raw_points[i]);
            }
        }
    }
    
    int unique_n = distinct_points.size();

    // 3. Duplicate for circularity
    const double PI = acos(-1.0);
    for (int i = 0; i < unique_n; ++i) {
        distinct_points.push_back({distinct_points[i].angle + 2 * PI, distinct_points[i].value});
    }
    
    // Calculate max allowed angle
    // Area = 0.5 * r^2 * theta  =>  theta = 2 * Area / r^2
    double theta_max = (2.0 * A) / (r * r);
    
    // Case 1: Maximize positive sum
    long long ans1 = get_max_subarray(unique_n, theta_max, distinct_points);
    
    // Case 2: Maximize negative sum (by negating values)
    vector<Topping> negated_points = distinct_points;
    for (auto& p : negated_points) p.value = -p.value;
    
    long long ans2 = get_max_subarray(unique_n, theta_max, negated_points);
    
    cout << max(ans1, ans2) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}