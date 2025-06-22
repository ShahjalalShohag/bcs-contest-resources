#include <bits/stdc++.h>
using namespace std;
 
#define double long double
 
const double eps = 1e-12;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
 
struct PT {
    double x, y;
    PT() { x = 0;  y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator <  (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator >  (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
};
 
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
 
struct HP {
    PT a, b;
    bool strict;
 
    HP() : a(), b(), strict(false) {}
    HP(PT a, PT b, bool strict) : a(a), b(b), strict(strict) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b), strict(rhs.strict) {}
 
    bool inside(const PT &p) const {
        double val = cross(b - a, p - a);
        if (strict)   return (val >  +eps);
        else          return (val >= -eps);
    }
 
    int operator < (const HP& rhs) const {
        PT p = b - a;
        PT q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (fabsl(p.y) < eps && p.x < 0));
        int fq = (q.y < 0 || (fabsl(q.y) < eps && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
 
    PT line_line_intersection(PT A, PT B, PT C, PT D) const {
        B = B - A;
        D = C - D;
        C = C - A;
        return A + B * (cross(C, D) / cross(B, D));
    }
 
    PT intersection(const HP &v) const {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
 
bool check(const HP &a, const HP &b, const HP &c) {
    PT I = b.intersection(c);
    return a.inside(I);
}
 
vector<PT> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < (int)h.size(); i++) {
        if (i == 0 || fabsl( cross(h[i].b - h[i].a, h[i - 1].b - h[i - 1].a) ) > eps) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
 
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
 
    for (int i = 0; i < (int)h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe-2], q[qe-1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh],   q[qh+1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh],     q[qe-2], q[qe-1])) qe--;
    while (qe - qh > 2 && !check(q[qe-1],   q[qh],   q[qh+1])) qh++;
 
    vector<HP> res;
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<PT> hull;
    if (res.size() > 2) {
        for (int i = 0; i < (int)res.size(); i++) {
            hull.push_back(res[i].intersection( res[(i + 1) % (int)res.size()] ));
        }
    }
    return hull;
}
 
bool canAchieveMaxArea(const vector<PT> &poly, double maxArea) {
    int n = (int)poly.size();
    vector<HP> halfplanes;
    halfplanes.reserve(2 * n);
 
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        PT edge = poly[j] - poly[i];
        halfplanes.emplace_back(poly[i], poly[i] + edge, true);
    }
 
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double dx = poly[j].x - poly[i].x;
        double dy = poly[j].y - poly[i].y;
        double R  = 2.0L * maxArea
                  + dx * poly[i].y
                  - dy * poly[i].x;
 
        PT base;
        if (fabsl(dy) > eps) {
            base = PT(-R / dy, 0.0L);
        } else {
            base = PT(0.0L, R / dx);
        }
        PT dir = PT(-dx, -dy);
        halfplanes.emplace_back(base, base + dir, false);
    }
 
    vector<PT> inter = half_plane_intersection(halfplanes);
    return (!inter.empty());
}
 
double solve(const vector<PT> &poly) {
    int n = (int)poly.size();
    double area2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    double polygon_area = fabsl(area2) * 0.5L;
 
    double lo = 0.0L, hi = polygon_area;
    for (int iter = 0; iter < 60; iter++) {
        double mid = 0.5L * (lo + hi);
        if (canAchieveMaxArea(poly, mid))
            hi = mid;
        else
            lo = mid;
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
        long long xi, yi;
        cin >> xi >> yi;
        poly[i] = PT((double)xi, (double)yi);
    }
 
    double ans = solve(poly);
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
