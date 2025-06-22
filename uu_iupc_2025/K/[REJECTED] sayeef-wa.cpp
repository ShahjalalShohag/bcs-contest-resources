#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define fr(m) for(int i=0; i<m; i++)
#define fro(m) for(int i=1; i<m; i++)
#define frj(m) for(int j=0; j<m; j++)
#define frr(n) for(int i=n; i>=0; i--)
#define pb push_back
#define pf push_front
#define orr ||
#define nl '\n'
#define nll cout<<'\n'
#define mod 1000000007
#define inf (1LL<<61)
#define inff (1<<30)
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 600005
 
int n, arr[mxn], vis[mxn], m[mxn];
vector<int>factors[mxn], divs[mxn];
ll ans=0;
 
void gen(int in, int cnt, int val, int now){
    if(in==factors[val].size()){
        if(cnt&1) ans+=m[now];
        else ans-=m[now];
        return;
    }
    gen(in+1,cnt+1,val,now*factors[val][in]);
    gen(in+1,cnt,val,now);
}
 
int main()
{
    fastio;
    for(int i=2; i<mxn; i++){
        if(!vis[i]){
            for(int j=i; j<mxn; j+=i){
                vis[j]=1;
                factors[j].pb(i);
            }
        }
    }
    for(int i=2; i<mxn; i++){
        for(int j=i; j<mxn; j+=i){
            divs[j].pb(i);
        }
    }
    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n+2; i++) m[i]=0;
        fr(n) cin>>arr[i];

        fr(n){
            for(int a : divs[arr[i]]) m[a]++;
            gen(0,0,arr[i],1);
        }
        ans=((ll)n*(n+1))/2-ans;
        cout<<ans<<nl;
    }
    return 0;
}