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
      ll a[n];
      for(ll i=0;i<n;i++) cin >> a[i];

      cout << (((a[0]==1 && a[n-1]==2) || (a[0]==2 && a[n-1]==1)) ? "YES" : "NO") <<endl;
       
   }
   return 0;
}
/*
3
3
1 3 2
4
1 2 3 4
5
3 1 4 2 5

output:
Yes
No
No
*/
