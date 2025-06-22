#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
};

inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }

bool is_parallel(PT a, PT b, PT c, PT d) {
    return sign(cross(b - a, d - c)) == 0;
}

bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (sign(det) == 0) return false;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return true;
}

vector<PT> cut(vector<PT> &p, PT a, PT b) {
    vector<PT> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        double c1 = cross(b - a, p[i] - a);
        double c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sign(c1) >= 0) ans.push_back(p[i]);
        if (sign(c1 * c2) < 0) {
            if (!is_parallel(p[i], p[(i + 1) % n], a, b)) {
                PT tmp;
                line_line_intersection(p[i], p[(i + 1) % n], a, b, tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}

double polygonArea(const vector<PT> &poly) {
    if (poly.size() < 3) return 0;
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        area += cross(poly[i], poly[(i + 1) % n]);
    }
    return abs(area) / 2.0;
}

bool canAchieveMaxArea(const vector<PT> &polygon, double maxArea) {
    int n = polygon.size();
    
    vector<PT> feasibleRegion = {
        PT(-1e9, -1e9), PT(1e9, -1e9), PT(1e9, 1e9), PT(-1e9, 1e9)
    };
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        feasibleRegion = cut(feasibleRegion, polygon[i], polygon[j]);
        if (feasibleRegion.empty()) return false;
    }
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double dx = polygon[j].x - polygon[i].x;
        double dy = polygon[j].y - polygon[i].y;
        double RHS = 2.0 * maxArea + dx * polygon[i].y - dy * polygon[i].x;
        
        PT a;
        if (abs(dx) > eps) {
            a = PT(0, RHS / dx);
        } else if (abs(dy) > eps) {
            a = PT(-RHS / dy, 0);
        } else {
            continue;
        }
        
        PT b = a + PT(-dx, -dy);
        feasibleRegion = cut(feasibleRegion, a, b);
        if (feasibleRegion.empty()) return false;
    }
    
    return !feasibleRegion.empty();
}

double solve(const vector<PT> &polygon) {
    double lo = 0, hi = polygonArea(polygon);;
    for (int iter = 0; iter < 60; iter++) {
        double mid = (lo + hi) / 2.0;
        if (canAchieveMaxArea(polygon, mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    return hi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<PT> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }
    
    double result = solve(polygon);
    cout << fixed << setprecision(6) << result << "\n";
    
    return 0;
}