#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
 
using namespace std;
 
struct Point {
    int x, y;
    int index;
};
 
long long cross_product(const Point& p1, const Point& p2, const Point& p3) {
    return 1LL * (p2.x - p1.x) * (p3.y - p1.y) - 1LL * (p2.y - p1.y) * (p3.x - p1.x);
}
 
bool is_point_inside_triangle(const Point& p, const Point& a, const Point& b, const Point& c) {
    long long c1 = cross_product(a, b, p);
    long long c2 = cross_product(b, c, p);
    long long c3 = cross_product(c, a, p);
    
    return (c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0);
}
 
long long dist_squared(const Point& a, const Point& b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}
 
void solve() {
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].index = i;
    }
    
    long long sum_x = 0, sum_y = 0;
    for (const auto& p : points) {
        sum_x += p.x;
        sum_y += p.y;
    }
    Point center = {static_cast<int>(sum_x / n), static_cast<int>(sum_y / n), -1};
    
    sort(points.begin(), points.end(), [&center](const Point& a, const Point& b) {
        return dist_squared(a, center) < dist_squared(b, center);
    });
    
    int limit = min(n, 20);
    for (int j = 0; j < limit; j++) {
        for (int k = j + 1; k < limit; k++) {
            for (int l = k + 1; l < limit; l++) {
                for (int i = 0; i < n; i++) {
                    if (i == j || i == k || i == l) continue;
                    
                    if (is_point_inside_triangle(points[i], points[j], points[k], points[l])) {
                        cout << points[i].index+1 << " " << points[j].index+1 << " ";
                        cout << points[k].index+1 << " " << points[l].index+1 << endl;
                        return;
                    }
                }
            }
        }
    }
    
    int start_idx = max(0, n - 20);
    for (int j = start_idx; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
            for (int l = k + 1; l < n; l++) {
                for (int i = 0; i < n; i++) {
                    if (i == j || i == k || i == l) continue;
                    
                    if (is_point_inside_triangle(points[i], points[j], points[k], points[l])) {
                        cout << points[i].index+1 << " " << points[j].index+1 << " ";
                        cout << points[k].index+1 << " " << points[l].index+1 << endl;
                        return;
                    }
                }
            }
        }
    }
    
    if (n > 20) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        
        // Select 20 random indices
        vector<int> random_indices;
        vector<bool> selected(n, false);
        
        while (random_indices.size() < min(20, n)) {
            int idx = generator() % n;
            if (!selected[idx]) {
                random_indices.push_back(idx);
                selected[idx] = true;
            }
        }
        
        for (int j_idx = 0; j_idx < random_indices.size(); j_idx++) {
            int j = random_indices[j_idx];
            for (int k_idx = j_idx + 1; k_idx < random_indices.size(); k_idx++) {
                int k = random_indices[k_idx];
                for (int l_idx = k_idx + 1; l_idx < random_indices.size(); l_idx++) {
                    int l = random_indices[l_idx];
                    
                    for (int i = 0; i < n; i++) {
                        if (i == j || i == k || i == l) continue;
                        
                        if (is_point_inside_triangle(points[i], points[j], points[k], points[l])) {
                            cout << points[i].index+1 << " " << points[j].index+1 << " ";
                            cout << points[k].index+1 << " " << points[l].index+1 << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    
    cout << "-1" << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}