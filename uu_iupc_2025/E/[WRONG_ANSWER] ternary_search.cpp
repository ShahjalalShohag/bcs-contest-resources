#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double t) const { return Point(x * t, y * t); }
};

double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double triangleArea(const Point& a, const Point& b, const Point& c) {
    return 0.5 * abs(cross(b - a, c - a));
}

bool isStrictlyInside(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (cross(poly[j] - poly[i], p - poly[i]) <= EPS) {
            return false;
        }
    }
    return true;
}

double getMaxTriangleArea(const vector<Point>& poly, const Point& q) {
    if (!isStrictlyInside(poly, q)) {
        return 1e18;
    }
    
    int n = poly.size();
    double maxArea = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        maxArea = max(maxArea, triangleArea(poly[i], poly[j], q));
    }
    return maxArea;
}

double ternarySearchY(const vector<Point>& poly, double x, double minY, double maxY) {
    for (int iter = 0; iter < 100; iter++) {
        double y1 = minY + (maxY - minY) / 3.0;
        double y2 = minY + 2.0 * (maxY - minY) / 3.0;
        
        double area1 = getMaxTriangleArea(poly, Point(x, y1));
        double area2 = getMaxTriangleArea(poly, Point(x, y2));
        
        if (area1 > area2) {
            minY = y1;
        } else {
            maxY = y2;
        }
    }
    return getMaxTriangleArea(poly, Point(x, (minY + maxY) / 2.0));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<Point> poly(n);
    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }
    
    double minX = poly[0].x, maxX = poly[0].x;
    double minY = poly[0].y, maxY = poly[0].y;
    
    for (int i = 0; i < n; i++) {
        minX = min(minX, poly[i].x);
        maxX = max(maxX, poly[i].x);
        minY = min(minY, poly[i].y);
        maxY = max(maxY, poly[i].y);
    }
    
    double result = 1e18;
    
    for (int iter = 0; iter < 100; iter++) {
        double x1 = minX + (maxX - minX) / 3.0;
        double x2 = minX + 2.0 * (maxX - minX) / 3.0;
        
        double area1 = ternarySearchY(poly, x1, minY, maxY);
        double area2 = ternarySearchY(poly, x2, minY, maxY);
        
        result = min(result, min(area1, area2));
        
        if (area1 > area2) {
            minX = x1;
        } else {
            maxX = x2;
        }
    }
    
    cout << fixed << setprecision(10) << result << endl;
    
    return 0;
}