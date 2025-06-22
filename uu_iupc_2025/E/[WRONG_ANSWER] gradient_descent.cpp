#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;

struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double _x, double _y) : x(_x), y(_y) {}
    PT operator + (const PT &o) const { return PT(x + o.x, y + o.y); }
    PT operator - (const PT &o) const { return PT(x - o.x, y - o.y); }
    PT operator * (double k)   const { return PT(x * k,   y * k  ); }
    PT operator / (double k)   const { return PT(x / k,   y / k  ); }
};

inline double cross(const PT &a, const PT &b) {
    return a.x*b.y - a.y*b.x;
}

inline double triangleArea(const PT &A, const PT &B, const PT &C) {
    return 0.5 * fabs(cross(B - A, C - A));
}

bool isInside(const PT &q, const vector<PT> &poly) {
    int n = poly.size();
    for(int i = 0; i < n; i++){
        const PT &p = poly[i];
        const PT &r = poly[(i+1)%n];
        double c = cross(r - p, q - p);
        if (c <= eps) return false;
    }
    return true;
}

PT computeGradient(const PT &q, const vector<PT> &poly, double &maxArea) {
    int n = poly.size();
    double bestA = -1e300;
    PT sumGrad{0,0};
    int cnt = 0;

    for(int i = 0; i < n; i++){
        const PT &p = poly[i];
        const PT &r = poly[(i+1)%n];
        double a = triangleArea(p, r, q);
        PT grad = PT(-(r.y - p.y)*0.5, (r.x - p.x)*0.5);

        if (fabs(a - bestA) < eps) {
            sumGrad = sumGrad + grad;
            cnt++;
        }
        else if (a > bestA) {
            bestA = a;
            sumGrad = grad;
            cnt = 1;
        }
    }
    maxArea = bestA;
    sumGrad = sumGrad / cnt;  // average
    return sumGrad;
}

// PT computeCentroid(const vector<PT> &p) {
//     int n = p.size();
//     double sum_x = 0, sum_y = 0;
//     for (int i = 0; i < n; ++i) {
//         sum_x += p[i].x;
//         sum_y += p[i].y;
//     }

//     PT centroid_q = PT(sum_x / n, sum_y / n);
//     return centroid_q;
// }
PT computeCentroid(const vector<PT> &poly) {
    int n = poly.size();
    double A2 = 0, cx = 0, cy = 0;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        double cr = cross(poly[i], poly[j]);
        A2 += cr;
        cx += (poly[i].x + poly[j].x) * cr;
        cy += (poly[i].y + poly[j].y) * cr;
    }
    double A = A2 * 0.5;
    return PT(cx/(6*A), cy/(6*A));
}

PT projectInside(PT q, const vector<PT> &poly, const PT &centroid) {
    for(int iter = 0; iter < 10; iter++){
        if (isInside(q, poly)) return q;
        q = PT( (q.x + centroid.x)*0.5,
                (q.y + centroid.y)*0.5 );
    }
    return centroid;
}

double computeMaxArea(const PT &q, const vector<PT> &poly) {
    double M = 0;
    int n = poly.size();
    for(int i = 0; i < n; i++){
        int j = (i+1)%n;
        M = max(M, triangleArea(poly[i], poly[j], q));
    }
    return M;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<PT> poly(n);
    for(int i = 0; i < n; i++){
        double x,y;
        cin >> x >> y;
        poly[i] = PT(x,y);
    }

    PT centroid = computeCentroid(poly);
    PT q = centroid;
    double bestA = computeMaxArea(q, poly);

    double step = 1.0;
    for(int iter = 0; iter < 10000; iter++){
        double currentMax;
        PT grad = computeGradient(q, poly, currentMax);

        PT q2 = PT(q.x - step * grad.x, q.y - step * grad.y);
        q2 = projectInside(q2, poly, centroid);

        double newMax = computeMaxArea(q2, poly);
        if (newMax + eps < bestA) {
            q = q2;
            bestA = newMax;
            step = min(step*1.1, 1e6);
        } else {
            step *= 0.5;
        }
        // if (step < eps) break;
    }

    cout << fixed << setprecision(6) << bestA << "\n";
    return 0;
}
