#include <bits/stdc++.h>

using namespace std;

struct PT {
    double x, y;
};

double cross_product(pair<int, int> p1, pair<int, int> p2, PT p3) {
    return (static_cast<double>(p2.first) - static_cast<double>(p1.first)) * (p3.y - static_cast<double>(p1.second)) -
           (static_cast<double>(p2.second) - static_cast<double>(p1.second)) * (p3.x - static_cast<double>(p1.first));
}

double triangle_area(pair<int, int> p1, pair<int, int> p2, PT p3) {
    return 0.5 * abs(cross_product(p1, p2, p3));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> p(n);

    long long sum_x = 0;
    long long sum_y = 0;

    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
        sum_x += p[i].first;
        sum_y += p[i].second;
    }

    PT centroid_q = {static_cast<double>(sum_x) / n, static_cast<double>(sum_y) / n};

    double max_area = 0.0; 
    for (int i = 0; i < n; ++i) {
        pair<int, int> p1 = p[i];
        pair<int, int> p2 = p[(i + 1) % n];
        
        max_area = max(max_area, triangle_area(p1, p2, centroid_q));
    }

    cout << fixed << setprecision(10) << max_area << endl;

    return 0;
}