#include <bits/stdc++.h>
using namespace std;

using Point = pair<int, int>;

int orientation(const Point& a, const Point& b, const Point& c) {
    long long cross = 1LL * (b.first - a.first) * (c.second - a.second) -
                      1LL * (b.second - a.second) * (c.first - a.first);
    return (cross > 0) - (cross < 0);
}

vector<int> convex_hull_indices(const vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return {0};

    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[i] = i;
    }

    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return points[i] < points[j];
    });

    vector<int> up, dn;
    for (int i : idx) {
        while (up.size() > 1 && orientation(points[up[up.size() - 2]], points[up.back()], points[i]) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(points[dn[dn.size() - 2]], points[dn.back()], points[i]) <= 0) {
            dn.pop_back();
        }
        up.push_back(i);
        dn.push_back(i);
    }

    vector<int> hull = dn;
    if (hull.size() > 1) hull.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (int i : up) {
        hull.push_back(i);
    }
    if (hull.size() == 2 && points[hull[0]] == points[hull[1]]) hull.pop_back();
    return hull;
}

// Check if point P lies strictly inside triangle ABC
bool is_inside(const Point& P, const Point& A, const Point& B, const Point& C) {
    long long cp1 = 1LL * (B.first - A.first) * (P.second - A.second) - 1LL * (B.second - A.second) * (P.first - A.first);
    long long cp2 = 1LL * (C.first - B.first) * (P.second - B.second) - 1LL * (C.second - B.second) * (P.first - B.first);
    long long cp3 = 1LL * (A.first - C.first) * (P.second - C.second) - 1LL * (A.second - C.second) * (P.first - C.first);
    return (cp1 > 0 && cp2 > 0 && cp3 > 0) || (cp1 < 0 && cp2 < 0 && cp3 < 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Point> points(n);
        for (auto& p : points) {
            cin >> p.first >> p.second;
        }

        vector<int> hull = convex_hull_indices(points);
        vector<bool> is_on_hull(n, false);

        for (int idx : hull) {
            is_on_hull[idx] = true;
        }

        int interior_point = -1;
        for (int i = 0; i < n; ++i) {
            if (!is_on_hull[i]) {
                interior_point = i;
                break;
            }
        }

        if (interior_point == -1) {
            cout << -1 << '\n';
            continue;
        }

        int j = hull[0];
        int m = hull.size();
        bool found = false;
        for (int idx = 0; idx < m; ++idx) {
            int k = hull[idx];
            int l = hull[(idx + 1) % m];
            if (k == j || l == j) continue;
            if (is_inside(points[interior_point], points[j], points[k], points[l])) {
                cout << interior_point + 1 << ' ' << j + 1 << ' ' << k + 1 << ' ' << l + 1 << '\n';
                found = true;
                break;
            }
        }

        assert(found);

        // if (!found) {
        //     cout << -1 << '\n';
        // }
    }

    return 0;
}
