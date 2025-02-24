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
    set<int> st[2];
    for(int i=1;i<=n;i++) st[i%2].insert(i);
    queue<int> q;
    q.push(0);
    ans[0]=0;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();


        int i = (x+k) % 2;

        int mn = min(k+x, -k+2*n-x);
        int lft = max(k-x, x-k);

        while(true)
        {
            auto it = st[i].lower_bound(lft);
            if(it == st[i].end()) break;
            if(*it > mn) break;
            ans[*it] = ans[x]+1;
            q.push(*it);
            st[i].erase(it);
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