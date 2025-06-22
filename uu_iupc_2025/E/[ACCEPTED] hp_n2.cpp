#include <bits/stdc++.h>
using namespace std;

#define double long double
const double eps = 1e-12;
const double PI = acosl(-1.0L);

struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double _x, double _y) : x(_x), y(_y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (double t) const { return PT(x * t, y * t); }
    PT operator / (double t) const { return PT(x / t, y / t); }
    
    double norm() const { return sqrtl(x * x + y * y); }
    PT normalize() const { 
        double len = norm();
        return (len > eps) ? (*this / len) : PT(0, 0);
    }
    PT perp() const { return PT(-y, x); }
};

double cross(const PT &a, const PT &b) {
    return a.x * b.y - a.y * b.x;
}

// Half-plane: all points q such that cross(b - a, q - a) >= 0
struct HP {
    PT a, b;
    HP() {}
    HP(const PT &_a, const PT &_b) : a(_a), b(_b) {}
    
    bool operator < (const HP &rhs) const {
        PT u = b - a, v = rhs.b - rhs.a;
        bool fu = (u.y < 0 || (u.y == 0 && u.x < 0));
        bool fv = (v.y < 0 || (v.y == 0 && v.x < 0));
        if (fu != fv) return fu < fv;
        double cr = cross(u, v);
        if (abs(cr) > eps) return cr > 0;
        return cross(u, rhs.a - a) < 0;
    }
    
    PT intersection(const HP &rhs) const {
        PT u = b - a, v = rhs.b - rhs.a;
        double t = cross(rhs.a - a, v) / cross(u, v);
        return a + u * t;
    }
    
    bool inside(const PT &p) const {
        return cross(b - a, p - a) >= -eps;
    }
};

vector<PT> half_plane_intersection(vector<HP> planes) {
    if (planes.empty()) return {};
    
    vector<PT> poly = {
        PT(-1e9, -1e9), PT(1e9, -1e9), 
        PT(1e9, 1e9), PT(-1e9, 1e9)
    };
    
    for (const HP &hp : planes) {
        vector<PT> new_poly;
        
        for (int i = 0; i < poly.size(); i++) {
            int j = (i + 1) % poly.size();
            PT curr = poly[i];
            PT next = poly[j];
            
            bool curr_in = hp.inside(curr);
            bool next_in = hp.inside(next);
            
            if (curr_in && next_in) {
                new_poly.push_back(next);
            } else if (curr_in && !next_in) {
                PT u = next - curr;
                PT v = hp.b - hp.a;
                double denom = cross(u, v);
                if (abs(denom) > eps) {
                    double t = cross(hp.a - curr, v) / denom;
                    if (t >= 0 && t <= 1) {
                        new_poly.push_back(curr + u * t);
                    }
                }
            } else if (!curr_in && next_in) {
                PT u = next - curr;
                PT v = hp.b - hp.a;
                double denom = cross(u, v);
                if (abs(denom) > eps) {
                    double t = cross(hp.a - curr, v) / denom;
                    if (t >= 0 && t <= 1) {
                        new_poly.push_back(curr + u * t);
                    }
                }
                new_poly.push_back(next);
            }
        }
        
        poly = new_poly;
        if (poly.size() < 3) break;
    }
    
    return poly;
}

bool canAchieveMaxArea(const vector<PT> &poly, double maxArea) {
    int n = poly.size();
    vector<HP> halfplanes;
    halfplanes.reserve(2 * n);
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;        
        halfplanes.emplace_back(poly[i], poly[j]);
    }
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double dx = poly[j].x - poly[i].x;
        double dy = poly[j].y - poly[i].y;
        
        double RHS = 2.0L * maxArea + dx * poly[i].y - dy * poly[i].x;
        
        PT base;
        if (abs(dy) > eps) {
            base = PT(-RHS / dy, 0);
        } else if (abs(dx) > eps) {
            base = PT(0, RHS / dx);
        } else {
            base = PT(0, 0);
        }
        
        PT dir = PT(-dx, -dy);
        
        halfplanes.emplace_back(base, base + dir);
    }
    
    vector<PT> intersection = half_plane_intersection(halfplanes);
    return !intersection.empty();
}

double solve(const vector<PT> &poly) {
    int n = poly.size();
    
    double area2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    double polygon_area = abs(area2) * 0.5L;
    
    double lo = 0, hi = polygon_area;
    for (int iter = 0; iter < 60; iter++) {
        double mid = (lo + hi) * 0.5L;
        if (canAchieveMaxArea(poly, mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    return hi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<PT> poly(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        poly[i] = PT(x, y);
    }
    
    double answer = solve(poly);
    cout << fixed << setprecision(10) << answer << "\n";
    
    return 0;
}