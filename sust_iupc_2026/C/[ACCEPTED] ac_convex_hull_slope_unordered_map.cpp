#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point {
    int x, y, id;
};

struct Dir {
    int dx, dy;

    bool operator<(const Dir &other) const {
        if (dx != other.dx) return dx < other.dx;
        return dy < other.dy;
    }

    bool operator==(const Dir &other) const {
        return dx == other.dx && dy == other.dy;
    }
};

ll cross(const Point &a, const Point &b, const Point &c) {
    return 1LL * (b.x - a.x) * (c.y - a.y)
         - 1LL * (b.y - a.y) * (c.x - a.x);
}

Dir normalize(int dx, int dy) {
    int g = gcd(abs(dx), abs(dy));

    dx /= g;
    dy /= g;

    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }

    return {dx, dy};
}

vector<int> convex_hull(const vector<Point> &points) {
    int m = points.size();

    vector<int> order(m);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](int a, int b) {
        if (points[a].x != points[b].x) {
            return points[a].x < points[b].x;
        }

        return points[a].y < points[b].y;
    });

    vector<int> hull;

    for (int id : order) {
        while ((int)hull.size() >= 2) {
            int b = hull.back();
            int a = hull[hull.size() - 2];

            if (cross(points[a], points[b], points[id]) > 0) {
                break;
            }

            hull.pop_back();
        }

        hull.push_back(id);
    }

    int lowerSize = hull.size();

    for (int i = m - 2; i >= 0; i--) {
        int id = order[i];

        while ((int)hull.size() > lowerSize) {
            int b = hull.back();
            int a = hull[hull.size() - 2];

            if (cross(points[a], points[b], points[id]) > 0) {
                break;
            }

            hull.pop_back();
        }

        hull.push_back(id);
    }

    hull.pop_back();

    return hull;
}

ll line_key(const Point &point, const Dir &direction) {
    return 1LL * direction.dx * point.y
         - 1LL * direction.dy * point.x;
}

int order_key(const Point &point, const Dir &direction) {
    if (direction.dx != 0) {
        return point.x;
    }

    return point.y;
}

bool try_direction(
    const vector<Point> &points,
    const Dir &direction,
    vector<pair<int, int>> &answer
) {
    unordered_map<ll, vector<int>> lines;
    lines.reserve(2 * points.size());
    lines.max_load_factor(0.7);

    for (int i = 0; i < (int)points.size(); i++) {
        lines[line_key(points[i], direction)].push_back(i);
    }

    answer.clear();

    for (auto &[key, ids] : lines) {
        if ((int)ids.size() % 2 == 1) {
            return false;
        }

        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return order_key(points[a], direction)
                 < order_key(points[b], direction);
        });

        for (int i = 0; i < (int)ids.size(); i += 2) {
            answer.push_back({
                points[ids[i]].id,
                points[ids[i + 1]].id
            });
        }
    }

    return true;
}

void solve() {
    int n;
    cin >> n;

    int m = 2 * n;

    vector<Point> points(m);

    for (int i = 0; i < m; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
    }

    vector<int> hull = convex_hull(points);
    vector<Dir> candidates;

    int hullSize = hull.size();

    for (int i = 0; i < hullSize; i++) {
        const Point &a = points[hull[i]];
        const Point &b = points[hull[(i + 1) % hullSize]];

        candidates.push_back(
            normalize(b.x - a.x, b.y - a.y)
        );
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(
        unique(candidates.begin(), candidates.end()),
        candidates.end()
    );

    vector<pair<int, int>> answer;

    for (const Dir &direction : candidates) {
        if (try_direction(points, direction, answer)) {
            for (auto [u, v] : answer) {
                cout << u << ' ' << v << '\n';
            }

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