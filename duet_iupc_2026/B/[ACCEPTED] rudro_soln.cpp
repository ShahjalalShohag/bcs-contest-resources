#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const ll N= 1e5+5;

int main(){
   FastIO;

   ll T=1; cin>>T;
   while(T--){
      ll n;cin>>n;
      ll a[n],cnt=0, fst=-1,lst=-1;
      for(ll i=0;i<n;i++){
      	cin>>a[i];
      	if(a[i]==1) cnt++;
      	else{
      		if(fst==-1) fst=i;
      		lst=i;
      	}
      }

      if(cnt==n) cout<<0<<"\n";
      else{
      	bool one=true;
      	for(ll i=fst+1;i<=lst;i++){
      		if(a[i]!=a[i-1]) one=false;
      	}
      	cout<< (one ? "1" : "2")<<"\n";
      }
       
   }
   return 0;
}
/*


*/
