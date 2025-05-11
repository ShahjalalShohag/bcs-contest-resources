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
      ll n,m; cin>>n>>m;
      ll ans[n+1][m+1],res=-1;
      if(n<=m){
         ll cur=1;
         res= min(n+n,m);
         for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
               if(i<=j) ans[i][j]= cur++; 
               else ans[i][j]= ans[i-1][j];
            }
         }
         for(ll i=1;i<=n;i++){
            for(ll j=n+1;j<=m;j++){
               if(j<=(i+n)) ans[i][j]= cur++;
               else ans[i][j]= ans[i][j-1];
            }
         }
      }
      else{ //m<n
         ll cur=1;
         res= min(m+m,n);
         for(ll i=1;i<=m;i++){
            for(ll j=1;j<=m;j++){
               if(j<=i) ans[i][j]= cur++; 
               else ans[i][j]= ans[i][j-1];
            }
         }
         for(ll i=m+1;i<=n;i++){
            for(ll j=1;j<=m;j++){
               if(i<=(j+m)) ans[i][j]= cur++;
               else ans[i][j]= ans[i-1][j];
            }
         }
      }

      //print answer
      cout<<res<<endl;
      for(ll i=1;i<=n;i++){
         for(ll j=1;j<=m;j++){
            cout<<ans[i][j]<<' ';
         }cout<<endl;
      }
       
   }
   return 0;
}
/*
2
4 7
7 4



Pattern:
n= 6,m= 4
1  1  1 1
2  3  3 3
4  5  6 6
7  8  9 10
11 12 9 10
15 12 9 10
*/
