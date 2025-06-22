#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define fr(m) for(int i=0; i<(m); i++)
#define fro(m) for(int i=1; i<(m); i++)
#define frj(m) for(int j=0; j<(m); j++)
#define frr(n) for(int i=(n); i>=0; i--)
#define pb push_back
#define pf push_front
#define orr ||
#define nl '\n'
#define nll cout<<'\n'
#define mod 1000000007
#define inf (1LL<<60)
#define inff (1<<30)-1
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 600005
 
int n, arr[mxn], vis[mxn], f[mxn], mul[mxn];
vector<pair<int,int>>factors[mxn]; 
vector<int>d[mxn];

int main()
{
    fastio;
    for(int i=2; i<mxn; i++){
        if(!vis[i]){
            for(int j=i; j<mxn; j+=i){
                vis[j]=1;
                int j2=j, a=1;
                while(j2%i==0){
                    j2/=i, a*=i;
                }
                factors[j].pb({i,a});
            }
        }
    }
    for(int i=1; i<mxn; i++){
        for(int j=i; j<mxn; j+=i){
            d[j].pb(i);
        }
    }

    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n+2; i++) f[i]=0, mul[i]=0;
 
        fr(n) cin>>arr[i], f[arr[i]]++;
 
        ll ans = 0;
        for(int i=1; i<=n; i++){
            if(f[i]){
                int m = factors[i].size();
                for(int msk=0; msk<(1<<m); msk++){
                    int a=1;
                    vector<int>b;
                    for(int j=0; j<m; j++){
                        if((msk>>j)&1) a*=factors[i][j].second;
                        else b.pb(factors[i][j].first);
                    }
                    if((ll)a*a<i){
                        a*=a;
                        ll tot=mul[a];
                        int m2=b.size();
                        for(int msk2=1; msk2<(1<<m2); msk2++){
                            int val=1, cnt=0;
                            for(int j=0; j<m2; j++){
                                if((msk2>>j)&1){
                                    val*=b[j];
                                    cnt++;
                                }
                            }
                            if(a*val<i){
                                if(cnt&1) tot-=mul[a*val];
                                else tot+=mul[a*val];
                            }
                        }
                        ans+=f[i]*tot;
                    }
                }
            }
            for(int dv : d[i]){
                mul[dv]+=f[i];
            }
        }
 
        if(f[1]){
            ans+=((ll)f[1]*(f[1]+1))/2;
        }
        
        cout<<ans<<'\n';
 
    }
    return 0;
}
