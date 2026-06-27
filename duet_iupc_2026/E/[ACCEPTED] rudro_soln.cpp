#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const ll N= 1e5+5;

/*
(x,y) mirror of x=y -> (y,x)
xi>yi -> below x=y
xi<yi -> upper x=y
xi=yi on the line
opt1: upper*low
opt2: zero*(upper+low)
opt3: zero*zero
*/

int main(){
   FastIO;

   ll T=1; cin>>T;
   while(T--){
      ll n; cin>>n;
      ll up=0,low=0,zero=0;
      for(ll i=0;i<n;i++){
      	ll x,y; cin>>x>>y;
      	if(x>y) low++;
      	else if(x<y) up++;
      	else zero++;
      }

      ll ans= low*up;
      ans+= (zero*(up+low));
      ans+= (zero*(zero-1))/2;

      cout<<ans<<"\n";

       
   }
   return 0;
}
/*

*/
