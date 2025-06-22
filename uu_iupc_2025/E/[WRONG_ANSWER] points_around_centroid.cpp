#include <bits/stdc++.h>
using namespace std;

struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double _x, double _y) : x(_x), y(_y) {}
    PT operator + (const PT &o) const { return PT(x + o.x, y + o.y); }
    PT operator - (const PT &o) const { return PT(x - o.x, y - o.y); }
    PT operator * (double k)   const { return PT(x * k,   y * k); }
    PT operator / (double k)   const { return PT(x / k,   y / k); }
};

inline double cross(const PT &a, const PT &b) {
    return a.x * b.y - a.y * b.x;
}

inline double triArea(const PT &A, const PT &B, const PT &C) {
    double c = cross(B - A, C - A);
    return 0.5 * fabs(c);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<PT> poly(n);
    long long sumX = 0, sumY = 0;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        poly[i] = PT(double(x), double(y));
        sumX += x;
        sumY += y;
    }

    PT centroid = PT(double(sumX) / n, double(sumY) / n);

    auto maxAreaAt = [&](const PT &q){
        double M = 0.0;
        for(int i = 0; i < n; i++){
            int j = (i+1) % n;
            double a = triArea(poly[i], poly[j], q);
            if(a > M) M = a;
        }
        return M;
    };

    double bestM = maxAreaAt(centroid);

    const int    GRID_STEPS = 600;
    const double STEP_SIZE  = 0.5;

    int half = GRID_STEPS / 2;
    for(int ix = -half; ix <= half; ix++){
        for(int iy = -half; iy <= half; iy++){
            if(ix == 0 && iy == 0) continue;
            PT q2 = PT(centroid.x + ix * STEP_SIZE,
                       centroid.y + iy * STEP_SIZE);
            double M2 = maxAreaAt(q2);
            if(M2 < bestM){
                bestM = M2;
            }
        }
    }

    cout << fixed << setprecision(6) << bestM << "\n";
    return 0;
}