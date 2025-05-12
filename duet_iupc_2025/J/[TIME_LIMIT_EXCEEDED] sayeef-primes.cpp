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
#define mod 998244353
#define inf (1LL<<60)
#define inff (1<<30)-1
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 300005

int n, k, arr[mxn];
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


bitset<mxn>vis;
vector<int>prime;

void sieve(){
    for(int i=2; i<mxn; i++){
        if(!vis[i]) prime.pb(i);
        for(int p : prime){
            if(p*i<mxn) vis[p*i]=1;
            else break;
            if(i%p==0) break;
        }
    }
}


int main()
{
    fastio;
    genfact();
    sieve();

    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n>>k;
        

        for(int i=0; i<n; i++){
            cin>>arr[i];
        }

        ll ans=0;

        for(int a : prime){
            if(a>n) break;
            int p = 0;
            for(int i=0; i<n; i++){
                if(arr[i]%a==0) p++;
            }
            ll now = (ncr(n,k) - ncr(n-p,k) + mod )%mod;
            now=(now*a)%mod;
            ans=(ans+now)%mod;
        }

        cout<<ans<<nl;
    }
    return 0;
}