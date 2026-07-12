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

    int m = item.size();
    vector<int> pref(m), val(m);

    pref[0] = item[0].second;
    for(i = 1; i < m; i++) pref[i] = pref[i - 1] + item[i].second;
    for(i = 0; i < m; i++) val[i] = item[i].first - i;

    int l = 0, r, len, mlen = 0;
    
    for(l = 0; l < m; l++)
    {
        r = upper_bound(val.begin(), val.end(), val[l]) - val.begin() - 1;
        len = l > 0? pref[r] - pref[l - 1]: pref[r];
 
        mlen = max(mlen, len);
    }
 
    cout << n - mlen;
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