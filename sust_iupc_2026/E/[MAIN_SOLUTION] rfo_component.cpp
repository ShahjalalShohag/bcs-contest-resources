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

    int cur = 1, len = 1;
    for(i = 1; i < n; i++)
    {
        if(v[i] <= v[i - 1] + 1)
        {
            cur++;
            len = max(len, cur);
        }

        else cur = 1;
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