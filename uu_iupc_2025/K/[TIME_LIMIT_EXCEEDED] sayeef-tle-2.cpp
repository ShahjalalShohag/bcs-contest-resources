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
#define mxn 1000005
 
int n, spf[10*mxn], arr[mxn], mul[10*mxn];

int main()
{
    fastio;
    for (int i = 1; i < 10*mxn; i++) spf[i] = i;
    for (int i = 2; i * i < 10*mxn; i++){
        if(spf[i] == i){ 
            for(int j = i * i; j <= 10*mxn; j+=i){
                if(spf[j] == j) { 
                    spf[j] = i;
                }
            }
        }
    }
    
 
    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<10*n+2; i++) mul[i]=0;
 
        fr(n) cin>>arr[i];
        sort(arr,arr+n);

        ll ans = 0;
        for(int i=n-1; i>=0; i--){
            if(arr[i]==1){
                break;
            }
            int num=arr[i];
            vector<int>hfacts;
            vector<pair<int,int>>facts;
            while(num>1){
                int fact = spf[num], j=0, hlf=1;
                while(num%fact==0){
                    num/=fact;
                    if(j&1) hlf*=fact;
                    j++;
                }
                hlf*=fact;
                hfacts.pb(hlf);
                facts.pb({fact,j});
            }
            
            int m=facts.size();
            vector<int>divs,ndivs;
            divs.pb(1);
            for(int j=0; j<m; j++){
                int now=1;
                ndivs.clear();
                for(int k=0; k<=facts[j].second; k++){
                    for(int a : divs){
                        ndivs.pb(a*now);
                    }
                    now*=facts[j].first;
                }
                divs=ndivs;
            }
            for(int a : divs){
                mul[a]++;
            }
            
            m = hfacts.size();
            ll val=0;
            for(int msk=0; msk<(1<<m); msk++){
                int a=1, parity=0;
                for(int j=0; j<m; j++){
                    if((msk>>j)&1) a*=hfacts[j], parity^=1;
                }
                if(1<a && a<=10*n){
                    if(parity&1) val+=mul[a];
                    else val-=mul[a];
                }
            }
            ans+=val;

        }
        
        cout<<((ll)n*(n+1))/2-ans<<'\n';
 
    }
    return 0;
}
