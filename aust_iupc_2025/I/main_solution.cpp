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
      ll n; cin>>n;
      vector<ll> a(n);
      for(ll i=0;i<n;i++) cin>>a[i];

      sort(all(a)); reverse(all(a));

      for(auto it: a) cout<<it<<' '; cout<<endl;
       
   }
   return 0;
}
/*
3
4
1 7 3 5
2
4 6
3
2 3 4

ans:
1 3 5 6 -> 0 1 2 3
4 6 -> 3 4
2 4 3 -> 1 2 0

*/
