/**
 * Problem: pizza_slice_shohag
 * Trap: Linear Solution (WA)
 * Reason: Fails to handle the circular wrap-around case. 
 * It misses optimal slices that cross the 0/360 degree boundary.
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

    // ERROR: We do NOT duplicate the array here for wrap-around
    vector<ld> angles;
    vector<ll> vals;
    for (int i = 0; i < n; i++)
    {
        angles.push_back(points[i].angle);
        vals.push_back(points[i].val);
    }

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + vals[i];

    ld max_theta = (2.0 * A) / (R * R);

    deque<int> min_dq, max_dq;
    min_dq.push_back(0);
    max_dq.push_back(0);

    int left = 0;
    ll max_profit = 0;

    // We only iterate up to n, missing the circular nature
    for (int right = 0; right < n; right++)
    {
        int curr_idx = right + 1;
        ll curr_val = pref[curr_idx];

        while (!min_dq.empty() && pref[min_dq.back()] >= curr_val) min_dq.pop_back();
        min_dq.push_back(curr_idx);

        while (!max_dq.empty() && pref[max_dq.back()] <= curr_val) max_dq.pop_back();
        max_dq.push_back(curr_idx);

        while (left <= right)
        {
            bool angle_ok = (angles[right] - angles[left]) <= (max_theta + 1e-9);
            if (angle_ok) break;

            if (!min_dq.empty() && min_dq.front() == left) min_dq.pop_front();
            if (!max_dq.empty() && max_dq.front() == left) max_dq.pop_front();
            left++;
        }

        if (!min_dq.empty() && !max_dq.empty())
        {
            ll current_spread = pref[max_dq.front()] - pref[min_dq.front()];
            max_profit = max(max_profit, current_spread);
        }
    }

    cout << max_profit << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t; while (t--) solve();
    return 0;
}