// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#ifdef LOKAL
#include "DEBUG_TEMPLATE.h"
#else
#define HERE
#define debug(args...)
#endif
typedef pair<int,int> pii;
#define ALL(x) x.begin(),x.end()

const int N = 3e5 +5;
const int oo = 1e9+7;


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int> ans(n+1,-1);
    queue<int> q;
    q.push(0);
    ans[0]=0;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();


        int rht = min(k+x, -k+2*n-x);
        int lft = max(k-x, x-k);
        int total_skip = 10;
        for(int i=lft;i<=rht;i+=2)
        {
            if(ans[i] == -1)
            {
                ans[i] = ans[x]+1;
                q.push(i);
            }
            else if(total_skip-- > 0)
            {
                ;
            }
            else break;
        }
        total_skip = 10;
        for(int i=rht;i>=lft;i-=2)
        {
            if(ans[i] == -1)
            {
                ans[i] = ans[x]+1;
                q.push(i);
            }
            else if(total_skip-- > 0)
            {
                ;
            }
            else break;
        }

    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<"\n";
}
/*

*/

int32_t main()
{
#ifndef LOKAL
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int T=1;
    cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
