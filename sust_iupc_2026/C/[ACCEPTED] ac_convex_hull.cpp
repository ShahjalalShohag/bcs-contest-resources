#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

using Point = tuple<int, int, int>;
using Node = tuple<ll, int, int, int>;

ll cross(const Point &a, const Point &b, const Point &c) {
    const auto &[ax, ay, _] = a;
    const auto &[bx, by, _] = b;
    const auto &[cx, cy, _] = c;

    return 1LL * (bx - ax) * (cy - ay)
         - 1LL * (by - ay) * (cx - ax);
}

vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());

    vector<Point> hull;
    hull.reserve(2 * points.size());

    for (const Point &point : points) {
        while ((int)hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }

        hull.push_back(point);
    }

    int lowerSize = hull.size();

    for (int i = (int)points.size() - 2; i >= 0; i--) {
        while ((int)hull.size() > lowerSize &&
               cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }

        hull.push_back(points[i]);
    }

    hull.pop_back();

    return hull;
}

bool try_direction(
    const vector<Point> &points,
    int dx,
    int dy,
    vector<ll> &key,
    vector<ll> &sortedKey,
    vector<Node> &nodes
) {
    int m = points.size();

    for (int i = 0; i < m; i++) {
        auto [x, y, id] = points[i];
        key[i] = 1LL * dx * y - 1LL * dy * x;
    }

    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

    for (int i = 0; i < m; i += 2) {
        if (sortedKey[i] != sortedKey[i + 1]) {
            return false;
        }
    }

    for (int i = 0; i < m; i++) {
        auto [x, y, id] = points[i];
        nodes[i] = {key[i], x, y, id};
    }

    sort(nodes.begin(), nodes.end());

    for (int i = 0; i < m; i += 2) {
        auto [key1, x1, y1, id1] = nodes[i];
        auto [key2, x2, y2, id2] = nodes[i + 1];

        cout << id1 << ' ' << id2 << '\n';
    }

    return true;
}

void solve() {
    int n;
    cin >> n;

    int m = 2 * n;

    vector<Point> points(m);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        points[i] = {x, y, i + 1};
    }

    vector<Point> hull = convex_hull(points);

    vector<ll> key(m);
    vector<ll> sortedKey(m);
    vector<Node> nodes(m);

    int hullSize = hull.size();

    for (int i = 0; i < hullSize; i++) {
        auto [ax, ay, idA] = hull[i];
        auto [bx, by, idB] = hull[(i + 1) % hullSize];

        int dx = bx - ax;
        int dy = by - ay;

        if (try_direction(points, dx, dy, key, sortedKey, nodes)) {
            return;
        }
    }

    cout << -1 << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}