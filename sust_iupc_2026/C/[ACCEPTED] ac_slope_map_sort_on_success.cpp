#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Point {
    int x, y;
    int id;
};

pii slope(const Point &a, const Point &b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;

    int g = gcd(abs(dx), abs(dy));

    dx /= g;
    dy /= g;

    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }

    return {dx, dy};
}

ll line_key(pii direction, const Point &point) {
    return 1LL * direction.first * point.y
         - 1LL * direction.second * point.x;
}

int order_key(pii direction, const Point &point) {
    if (direction.first != 0) {
        return point.x;
    }

    return point.y;
}

bool build_answer(
    const vector<Point> &points,
    pii direction,
    vector<pii> &answer
) {
    int m = points.size();

    map<ll, vector<int>> groups;

    for (int i = 0; i < m; i++) {
        groups[line_key(direction, points[i])].push_back(i);
    }

    for (auto &[key, group] : groups) {
        if ((int)group.size() % 2 == 1) {
            return false;
        }
    }

    answer.clear();

    for (auto &[key, group] : groups) {
        sort(group.begin(), group.end(), [&](int a, int b) {
            return order_key(direction, points[a])
                 < order_key(direction, points[b]);
        });

        for (int i = 0; i < (int)group.size(); i += 2) {
            answer.push_back({
                points[group[i]].id,
                points[group[i + 1]].id
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

    vector<pii> candidates;

    for (int i = 1; i < m; i++) {
        candidates.push_back(slope(points[0], points[i]));
    }

    sort(candidates.begin(), candidates.end());

    candidates.erase(
        unique(candidates.begin(), candidates.end()),
        candidates.end()
    );

    vector<pii> answer;

    for (pii direction : candidates) {
        if (build_answer(points, direction, answer)) {
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