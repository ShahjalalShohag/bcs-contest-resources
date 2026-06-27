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
    LL n, m, k;
    cin >> n >> m >> k;
 
    if(k <= n) cout << k;
    else if(m % 2 == 1) cout << n - (k - n) % 2;
    else if(k <= n * (m - 1)) cout << n - (k - n) % 2;
    else cout << n * m - k;
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