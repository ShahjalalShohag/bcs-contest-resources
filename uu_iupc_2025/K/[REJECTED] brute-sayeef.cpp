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

int n, arr[mxn], vis[mxn];
vector<int>factors[mxn]; 

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
    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        fr(n) cin>>arr[i];
        sort(arr,arr+n);

        ll ans=0;

        for(int i=0; i<n; i++){
            for(int j=0; j<=i; j++){
                int flag=1;
                for(int a : factors[arr[i]]){
                    int c1=0, c2=0, b=arr[i];
                    while(b%a==0){
                        c1++, b/=a;
                    }
                    b=arr[j];
                    while(b%a==0){
                        c2++, b/=a;
                    }
                    if(c2!=0 && c2<2*c1){
                        flag=0;
                        break;
                    }

                }
                ans+=flag;
            }
        }

        cout<<ans<<'\n';

    }
    return 0;
}