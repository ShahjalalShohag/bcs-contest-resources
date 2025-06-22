#include <bits/stdc++.h>
using namespace std;

// A 2D point / vector
struct P {
    double x, y;
    P(){}
    P(double _x,double _y):x(_x),y(_y){}
    P operator+(const P &o) const { return P(x+o.x, y+o.y); }
    P operator-(const P &o) const { return P(x-o.x, y-o.y); }
    P operator*(double s) const { return P(x*s, y*s); }
};

// Cross product of a × b
static double cross(const P &a, const P &b) {
    return a.x*b.y - a.y*b.x;
}

// Clip a convex polygon 'poly' against the half‐plane
//   cross(e, q) <= C
// Produces the intersection in‐place.
void clip_halfplane(vector<P> &poly, const P &e, double C) {
    vector<P> out;
    int n = poly.size();
    if (n == 0) return;
    auto f = [&](const P &q){ return cross(e, q) <= C; };
    for (int i = 0; i < n; i++) {
        P A = poly[i];
        P B = poly[(i+1)%n];
        bool inA = f(A), inB = f(B);
        if (inA) {
            // A lies inside → keep it
            out.push_back(A);
        }
        // If edge AB crosses the boundary, emit intersection
        if (inA ^ inB) {
            // Solve for t in A + t*(B-A) where cross(e, ·) == C
            double FA = cross(e, A);
            double FB = cross(e, B);
            // t = (C - FA)/(FB - FA)
            double t = (C - FA)/(FB - FA);
            // Clamp just in case of numerical epsilons
            t = max(0.0, min(1.0, t));
            P I = A + (B - A)*t;
            out.push_back(I);
        }
    }
    poly.swap(out);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<P> poly(n);
    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }

    // Precompute edges e_i = p_{i+1} - p_i and constant base = cross(e_i, p_i)
    vector<P> edges(n);
    vector<double> base(n);
    for (int i = 0; i < n; i++) {
        P A = poly[i];
        P B = poly[(i+1)%n];
        edges[i] = B - A;
        base[i] = cross(edges[i], A);
    }

    // Binary‐search answer M = maximum triangle area
    double lo = 0, hi = 1e12;  // hi large enough for coordinates up to 1e6
    for (int iter = 0; iter < 60; iter++) {
        double mid = (lo + hi) / 2;
        // Start with the original polygon as the feasible region
        vector<P> clip_poly = poly;

        // For each edge we enforce 0 <= cross(e_i, q - p_i) <= 2*mid
        // The 0 <= … half is automatic since clip_poly is the original convex polygon.
        // We only need to clip with cross(e_i, q) <= 2*mid + base[i].
        bool empty = false;
        for (int i = 0; i < n; i++) {
            double C = 2*mid + base[i];
            clip_halfplane(clip_poly, edges[i], C);
            if (clip_poly.empty()) {
                empty = true;
                break;
            }
        }

        // If non‐empty, mid is feasible
        if (!empty) hi = mid;
        else        lo = mid;
    }

    // hi is our approximation of the minimum max‐area, print with 6 decimals
    cout << fixed << setprecision(6) << hi << "\n";
    return 0;
}
