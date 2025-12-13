#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;

// Using long double for extra precision "just in case"
#define double long double

struct Topping {
    double angle;
    long long value;
};

// Heuristic 1: Naive Sliding Window
// This finds the sum of the window [L, R] where R is fixed and L is 
// the furthest left possible. It assumes "bigger is better".
long long heuristic_naive_window(int n, double theta_max, const vector<Topping>& toppings) {
    long long max_val = 0;
    long long current_sum = 0;
    int left = 0;
    int count = 0;

    for (int right = 0; right < toppings.size(); ++right) {
        current_sum += toppings[right].value;
        count++;

        // Shrink from left if angle is too big or too many items
        // Note: checking angle diff > theta_max
        while (count > n || (toppings[right].angle - toppings[left].angle > theta_max + 1e-9)) {
            current_sum -= toppings[left].value;
            left++;
            count--;
        }
        
        max_val = max(max_val, abs(current_sum));
    }
    return max_val;
}

// Heuristic 2: "Constrained" Kadane
// Standard Kadane's, but if the segment gets too "wide" (angle-wise),
// we just give up on that segment and reset. This finds "small, dense" clusters.
long long heuristic_constrained_kadane(int n, double theta_max, const vector<Topping>& toppings) {
    long long max_so_far = 0;
    long long current_max = 0;
    int start_idx = 0;

    for (int i = 0; i < toppings.size(); ++i) {
        // Standard Kadane logic
        if (current_max + toppings[i].value > toppings[i].value) {
            current_max += toppings[i].value;
        } else {
            current_max = toppings[i].value;
            start_idx = i;
        }

        // Check if our current happy segment is actually valid
        bool valid = true;
        if ((i - start_idx + 1) > n) valid = false;
        if (valid && (toppings[i].angle - toppings[start_idx].angle > theta_max + 1e-9)) valid = false;

        if (valid) {
            max_so_far = max(max_so_far, current_max);
        } else {
            // HACK: If invalid, just hard reset. This is the flaw.
            // A correct algo would shrink from left efficiently.
            current_max = 0; 
            start_idx = i + 1;
        }
    }
    return max_so_far;
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
        raw_points[i] = {atan2((double)y, (double)x), v};
    }
    
    sort(raw_points.begin(), raw_points.end(), [](const Topping& a, const Topping& b) {
        return a.angle < b.angle;
    });
    
    // Merge collinear (Important correctness fix kept from main solution)
    vector<Topping> pts;
    if (n > 0) {
        pts.push_back(raw_points[0]);
        for (int i = 1; i < n; ++i) {
            if (abs(raw_points[i].angle - pts.back().angle) < 1e-9) {
                pts.back().value += raw_points[i].value;
            } else {
                pts.push_back(raw_points[i]);
            }
        }
    }
    
    // Duplicate for circularity
    int m = pts.size();
    double PI = acos(-1.0);
    for (int i = 0; i < m; ++i) {
        pts.push_back({pts[i].angle + 2 * PI, pts[i].value});
    }

    double theta_max = (2.0 * A) / (r * r);
    long long ans = 0;

    // Run heuristics on Positive values
    ans = max(ans, heuristic_naive_window(m, theta_max, pts));
    ans = max(ans, heuristic_constrained_kadane(m, theta_max, pts));

    // Run heuristics on Negative values (inverted)
    vector<Topping> neg_pts = pts;
    for(auto& p : neg_pts) p.value = -p.value;
    
    ans = max(ans, heuristic_naive_window(m, theta_max, neg_pts));
    ans = max(ans, heuristic_constrained_kadane(m, theta_max, neg_pts));

    // Extra Hack: Random sampling
    // Pick 30 random points and try to extend fully from them
    // This catches some cases where "Naive" shrinks too aggressively
    mt19937 rng(42); 
    for(int k=0; k<30; ++k) {
        int start = rng() % m;
        long long current_sum = 0;
        long long current_sum_neg = 0;
        for(int i = start; i < pts.size(); ++i) {
            if (pts[i].angle - pts[start].angle > theta_max + 1e-9) break;
            if (i - start >= m) break;

            current_sum += pts[i].value;
            current_sum_neg += (-pts[i].value); // check negative version too
            
            ans = max(ans, abs(current_sum));
            ans = max(ans, abs(current_sum_neg));
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}