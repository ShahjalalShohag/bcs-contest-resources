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

int n, arr[mxn], vis[mxn], f[mxn], f2[mxn];
vector<pair<int,int>>factors[mxn]; 

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
    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n+2; i++) f[i]=0, f2[i]=0;

        fr(n) cin>>arr[i], f[arr[i]]++;

        ll ans = 0;
        for(int i=1; i<=n; i++){
            // cout<<i<<" "<<f[i]<<endl;
            if(f[i]){
                int m = factors[i].size();
                for(int msk=0; msk<(1<<m); msk++){
                    int num=1;
                    vector<int>otfacts;
                    for(int j=0; j<m; j++){
                        if((msk>>j)&1) num*=factors[i][j].second;
                        else otfacts.push_back(factors[i][j].first);
                    }
                    if((ll)num*num<i){
                        for(int j=num*num; j<i; j+=num*num){
                            if(f2[j]){
                                int flag=1;
                                for(int b : otfacts){
                                    if(j%b==0){
                                        flag=0;
                                        break;
                                    }
                                }
                                if(flag){
                                    // cout<<"yes "<<i<<" "<<j<<" "<<num<<endl;
                                    ans+=(ll)f[i]*f2[j];
                                }
                            }
                        }
                    }
                }
            }
            f2[i]=f[i];
        }

        if(f[1]){
            ans+=((ll)f[1]*(f[1]+1))/2;
        }
        
        cout<<ans<<'\n';

    }
    return 0;
}