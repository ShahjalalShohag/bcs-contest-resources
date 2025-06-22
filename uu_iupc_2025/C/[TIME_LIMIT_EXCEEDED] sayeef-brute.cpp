#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define mod 998244353
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 1000005

ll fact[mxn], ifact[mxn];

ll bigmod(ll b, ll p, ll m){
    b%=m;
    ll ret=1, val=b;
    while(p){
        if(p&1) ret=(ret*val)%m;
        val=(val*val)%m, p>>=1;
    }
    return ret;
}

void genfact(){
    fact[0]=fact[1]=ifact[0]=ifact[1]=1;
    for(ll i=2; i<mxn; i++){
        fact[i]=(fact[i-1]*i)%mod;
        ifact[i]=bigmod(fact[i],mod-2,mod);
    }
}

ll ncr(ll n, ll r){
    if(n<0 || r<0 || n<r) return 0;
    return ifact[r]*ifact[n-r]%mod*fact[n]%mod;
}

int main()
{
    fastio;
    genfact();
    int t, tc=1;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        ll ans = 0;
        for(int i=1; i<=n; i++){
            for(int j=i; j<=n; j++){
                ll now = ncr(j,i);
                ans^=now;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}