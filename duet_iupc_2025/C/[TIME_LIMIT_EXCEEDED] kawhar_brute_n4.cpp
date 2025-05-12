#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct Point {
    int x, y;
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

void solve() {
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (i == j || i == k || i == l) continue;
                    
                    if (is_point_inside_triangle(points[i], points[j], points[k], points[l])) {
                        cout << i+1 << " " << j+1 << " " << k+1 << " " << l+1 << endl;
                        return;
                    }
                }
            }
        }
    }
    
    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; 
    cin >> t;
 
    while(t--) {
        solve();
    }
        
    return 0;
}