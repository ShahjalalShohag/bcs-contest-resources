/**
 * Problem: pizza_slice_shohag
 * Method: Brute Force (O(N^2))
 * Note: This will TLE on large constraints (N > 5000)
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const ld PI = acos(-1.0);

struct Point
{
    ld angle;
    ll val;
};

void solve()
{
    int n;
    ld R, A;
    cin >> n >> R >> A;

    vector<Point> raw_points;
    raw_points.reserve(n);

    for (int i = 0; i < n; i++)
    {
        ll x, y, v;
        cin >> x >> y >> v;
        Point p;
        p.val = v;
        p.angle = atan2((ld)y, (ld)x);
        raw_points.push_back(p);
    }

    // Sort by angle
    sort(raw_points.begin(), raw_points.end(), [](const Point &a, const Point &b)
         { return a.angle < b.angle; });

    // Merge duplicate angles
    vector<Point> points;
    if (!raw_points.empty())
    {
        points.push_back(raw_points[0]);
        for (size_t i = 1; i < raw_points.size(); ++i)
        {
            if (abs(raw_points[i].angle - points.back().angle) < 1e-9)
            {
                points.back().val += raw_points[i].val;
            }
            else
            {
                points.push_back(raw_points[i]);
            }
        }
    }

    n = points.size();

    if (n == 0) {
        cout << "0\n";
        return;
    }

    // Create circular buffer
    vector<ld> angles;
    vector<ll> vals;
    for (int i = 0; i < n; i++)
    {
        angles.push_back(points[i].angle);
        vals.push_back(points[i].val);
    }
    for (int i = 0; i < n; i++)
    {
        angles.push_back(points[i].angle + 2.0 * PI);
        vals.push_back(points[i].val);
    }

    // Prefix sums
    vector<ll> pref(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
        pref[i + 1] = pref[i] + vals[i];

    ld max_theta = (2.0 * A) / (R * R);
    ll max_profit = 0;

    // Brute Force: Check every possible slice [i, j]
    for (int i = 0; i < 2 * n; ++i)
    {
        for (int j = i; j < 2 * n; ++j)
        {
            // Constraint 1: Slice length cannot exceed N (wrap around more than once)
            // A slice from i to j includes (j - i + 1) points.
            if ((j - i + 1) > n) continue;

            // Constraint 2: Angular width check
            // Angle covered is angle of last point - angle of first point
            // Note: If i==j, width is 0.
            ld current_theta = angles[j] - angles[i];
            
            if (current_theta <= max_theta + 1e-9)
            {
                ll current_sum = pref[j + 1] - pref[i];
                max_profit = max(max_profit, abs(current_sum));
            }
            else
            {
                // Since angles are sorted, if [i, j] exceeds max_theta, 
                // any [i, j+1...] will also exceed it. Break inner loop optimization.
                break;
            }
        }
    }

    cout << max_profit << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
        solve();

    return 0;
}