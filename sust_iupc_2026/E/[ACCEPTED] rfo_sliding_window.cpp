#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
using PII = pair<int,int>;


void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int i, n;
    cin >> n;

    vector<int> v(n);
    for(auto &it: v) cin >> it;
    sort(v.begin(), v.end());

    vector<PII> item;
    item.push_back({v[0], 1});
    for(i = 1; i < n; i++)
    {
        if(v[i] == item.back().first) item.back().second++;
        else item.push_back({v[i], 1});
    }

    int mx, mn, uniq;
    int l = 0, r, m = item.size(), cur = 0, len = 0;
    
    for(r = 0; r < m; r++)
    {
        cur += item[r].second;

        mx = item[r].first;
        mn = item[l].first;
        uniq = r - l + 1;

        while(mx - mn >= uniq)
        {
            cur -= item[l].second;
            l++;

            mn = item[l].first;
            uniq = r - l + 1;
        }

        len = max(len, cur);
    }

    cout << n - len;
}

int main()
{
    pre();

    int tc, tt = 1;
    cin >> tt;
    
    for(tc = 1; tc <= tt; tc++)
    {
        // cout << "Case " << tc << ": ";
        solve(tc);
        cout << '\n';
    }

    return 0;
}