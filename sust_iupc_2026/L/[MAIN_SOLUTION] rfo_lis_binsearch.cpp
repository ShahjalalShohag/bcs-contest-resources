#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;



void pre()
{
    fastio;
    
    
}

void solve(int tc)
{
    int i, j, k, l, n;
    cin >> n >> k;
    
    vector<int> v(n);
    for(auto &it: v) cin >> it;
    
    LL s = 0, ans;
    vector<int> bucket;
    for(i = 0; i < n; i++)
    {
        s += v[i];
        
        if(bucket.empty() || v[i] > bucket.back()) bucket.push_back(v[i]);
        else
        {
            j = lower_bound(bucket.begin(), bucket.end(), v[i]) - bucket.begin();
            bucket[j] = v[i];
        }
        
        l = bucket.size();
        
        if(l > bucket.back()) ans = s + (2LL * l + k - 1) * k / 2;
        else ans = s + 1LL * l * k;
        
        cout << ans << " \n"[i == n - 1];
    }
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
    }
    
    return 0;
}