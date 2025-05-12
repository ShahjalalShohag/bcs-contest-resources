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
      ll ans[n+1][m+1],cnt=0;
      if(n<=m){
        for(ll j=1;j<=m;j++){
            for(ll i=1;i<=n;i++){
                if(i<=j) ans[i][j]= ++cnt;
                else ans[i][j]= ans[i-1][j];
            }
        }

      }else{
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=m;j++){
                if(j<=i) ans[i][j]= ++cnt;
                else ans[i][j]= ans[i][j-1];
            }
        }
      }

      //now just count the distinct number in this array

        set<int> dist_counts;
        for (int i = 1; i <= n; ++i) {
            set<int> row_elements;
            for (int j = 1; j <= m; ++j) {
                row_elements.insert(ans[i][j]);
            }
            dist_counts.insert(row_elements.size());
        }

        for (int j = 1; j <= m; ++j) {
            set<int> col_elements;
            for (int i = 1; i <= n; ++i) {
                col_elements.insert(ans[i][j]);
            }
            dist_counts.insert(col_elements.size());
        }


        cout << dist_counts.size() << endl;

        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=m;j++){
                cout<<ans[i][j]<<' ';
            }cout<<endl;
        }

       
   }
   return 0;
}
/*

*/
