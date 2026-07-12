#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct Point {
    int x, y;
    int id;
};

struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(ll x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        return splitmix64((uint64_t)x + FIXED_RANDOM);
    }
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

bool build_answer(
    const vector<Point> &points,
    pii direction,
    vector<pii> &answer
) {
    int m = points.size();

    unordered_map<ll, vector<int>, CustomHash> groups;
    groups.reserve(2 * m);

    for (int i = 0; i < m; i++) {
        groups[line_key(direction, points[i])].push_back(i);
    }

    answer.clear();

    for (auto &[key, group] : groups) {
        int size = group.size();

        if (size % 2 == 1) {
            return false;
        }

        for (int i = 0; i < size; i += 2) {
            int u = points[group[i]].id;
            int v = points[group[i + 1]].id;

            answer.push_back({u, v});
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

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }

        return a.y < b.y;
    });

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