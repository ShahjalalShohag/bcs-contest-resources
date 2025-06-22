#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mod 998244353
#define mxn 1000005

ll fact[mxn], ifact[mxn], v[mxn];

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
    for(int i=2; i<mxn; i+=2){
        v[i] = ncr(i,i/2);
    }
    for(int i=1; i<mxn; i++){
        v[i]^=v[i-1];
        v[i]%=mod;
    }

    int t, tc=1;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        cout<<(v[n]^(n%2))<<'\n';
    }
    return 0;
}