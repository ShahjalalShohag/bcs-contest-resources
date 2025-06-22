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
#define mxn changeit

int main()
{
    fastio;
    int t, tc=1;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        ll arr[n];
        fr(n){
            cin>>arr[i];
        }
        ll ans=0;
        for(int i=0; i<n; i++){
            for(int j=i; j<n; j++){
                ll g=__gcd(arr[i],arr[j]);
                ll l=(arr[i]*arr[j])/g;
                if((l/g)%max(arr[i],arr[j])==0) ans++;
            }
        }
        cout<<ans<<nl;
    }
    return 0;
}