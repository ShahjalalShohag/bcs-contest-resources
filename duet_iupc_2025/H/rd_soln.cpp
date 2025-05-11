#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const ll N= 1e5+5;

int main(){
   FastIO;

   ll T=1,ts=0,ns=0; cin>>T;
   assert(T>=1 && T<=10000);
   while(T--){
      ll n; cin>>n;
      ns+= n;
      assert(ns>=1 && ns<=300000);
      string s; cin>>s;
      ll ss=0,aa=0,bb=0;
      for(ll i=0;i<n;i++){
         assert(s[i]=='A' || s[i]=='B' || s[i]=='S');
      	ss+=(s[i]=='S');
      	aa+=(s[i]=='A');
      	bb+=(s[i]=='B');
      }
      if(aa==n || bb==n) cout<<n<<endl;
      else if(aa && bb) cout<<1<<endl;
      else if(ss!=n) cout<<max(aa,bb)<<endl;
      else cout<<2<<endl;
       
   }
   return 0;
}
/*

*/
