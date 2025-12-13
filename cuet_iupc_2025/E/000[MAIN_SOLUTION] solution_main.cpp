/**
 * Problem: pizza_slice_shohag
 * Method: Sliding Window + Multiset
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

    sort(raw_points.begin(), raw_points.end(), [](const Point &a, const Point &b)
         { return a.angle < b.angle; });

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

    vector<ll> pref(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
        pref[i + 1] = pref[i] + vals[i];

    ld max_theta = (2.0 * A) / (R * R);

    multiset<ll> window_prefs;
    window_prefs.insert(pref[0]);

    int left = 0;
    ll max_profit = 0;

    for (int right = 0; right < 2 * n; right++)
    {
        window_prefs.insert(pref[right + 1]);

        while (left <= right)
        {
            bool len_ok = (right - left) < n;
            bool angle_ok = (angles[right] - angles[left]) <= (max_theta + 1e-9);

            if (len_ok && angle_ok)
                break;

            auto it = window_prefs.find(pref[left]);
            if (it != window_prefs.end())
                window_prefs.erase(it);
            left++;
        }

        if (!window_prefs.empty())
        {
            ll current_spread = *window_prefs.rbegin() - *window_prefs.begin();
            max_profit = max(max_profit, current_spread);
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
    while (t--)
        solve();

    return 0;
}