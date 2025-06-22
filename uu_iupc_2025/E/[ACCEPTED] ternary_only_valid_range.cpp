#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double t)       const { return Point(x * t, y * t); }
};

double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double triangleArea(const Point& a, const Point& b, const Point& c) {
    return 0.5 * fabs(cross(b - a, c - a));
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
    double maxA = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double a = triangleArea(poly[i], poly[j], q);
        if (a > maxA) maxA = a;
    }
    return maxA;
}

bool get_y_range(const vector<Point>& poly, double x0, double &y_lo, double &y_hi) {
    int n = poly.size();
    vector<double> Ys;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double x1 = poly[i].x, y1 = poly[i].y;
        double x2 = poly[j].x, y2 = poly[j].y;
        
        if ((x1 <= x0 + EPS && x0 <= x2 + EPS) || (x2 <= x0 + EPS && x0 <= x1 + EPS)) {
            if (fabs(x2 - x1) < EPS) {
                Ys.push_back(y1);
                Ys.push_back(y2);
            } else {
                double t = (x0 - x1) / (x2 - x1);
                double y = y1 + (y2 - y1) * t;
                Ys.push_back(y);
            }
        }
    }
    if (Ys.empty()) return false;
    sort(Ys.begin(), Ys.end());
    y_lo = Ys[0] + EPS;
    y_hi = Ys.back() - EPS;
    return true;
}

double ternarySearchY(const vector<Point>& poly, double x0) {
    double y_lo, y_hi;
    if (!get_y_range(poly, x0, y_lo, y_hi)) {
        return 1e18;
    }
    if (y_hi - y_lo < EPS) {
        return getMaxTriangleArea(poly, Point(x0, 0.5*(y_lo + y_hi)));
    }
    for (int iter = 0; iter < 100; iter++) {
        double y1 = y_lo + (y_hi - y_lo) / 3.0;
        double y2 = y_lo + 2.0 * (y_hi - y_lo) / 3.0;
        double a1 = getMaxTriangleArea(poly, Point(x0, y1));
        double a2 = getMaxTriangleArea(poly, Point(x0, y2));
        if (a1 > a2) {
            y_lo = y1;
        } else {
            y_hi = y2;
        }
    }
    double y_mid = 0.5 * (y_lo + y_hi);
    return getMaxTriangleArea(poly, Point(x0, y_mid));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> poly(n);
    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }

    double minX = poly[0].x, maxX = poly[0].x;
    for (int i = 1; i < n; i++) {
        minX = min(minX, poly[i].x);
        maxX = max(maxX, poly[i].x);
    }

    double lo = minX, hi = maxX;
    double result = 1e18;
    for (int iter = 0; iter < 100; iter++) {
        double x1 = lo + (hi - lo) / 3.0;
        double x2 = lo + 2.0 * (hi - lo) / 3.0;
        double f1 = ternarySearchY(poly, x1);
        double f2 = ternarySearchY(poly, x2);
        result = min(result, min(f1, f2));
        if (f1 > f2) {
            lo = x1;
        } else {
            hi = x2;
        }
    }
    cout << fixed << setprecision(10) << result << "\n";
    return 0;
}
