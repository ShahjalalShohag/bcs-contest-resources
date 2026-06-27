#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const ll N= 1e6+5,MX=1e9;
vector<ll> dp[2]; 
ll a[N];
/*
dp[i][j]=max total contribution by dividing prefix of first i elements into exactly j segments.
dp[i][j]=max(0<=m<i)dp[j-1][m]+cost(m+1,i)
L[i]= closest prev position j, where a[j]>a[i]
for a pos j, it will contribute only in the range [L[i], j-1]
*/

int main(){
   FastIO;

   dp[0].assign(N, 0);
   dp[1].assign(N, 0);

   ll T=1; cin>>T;
   while(T--){
      ll n,k; cin>>n>>k;
      for(ll i=1;i<=n;i++) cin>>a[i],dp[0][i]=-MX;
      dp[0][0]=0;

      vector<ll> stack_max(n+1), tree_max(n+1);
      vector<ll> st;
      st.reserve(n+1);

      for(ll j=1;j<=k;j++){
        st.clear();
        
        for(ll i=1;i<=n;i++) dp[1][i]=stack_max[i]=tree_max[i]=-MX;
        
        for(ll i=1;i<=n;i++){
            ll cur= dp[0][i-1];
            while(!st.empty() && a[st.back()]<a[i]){
                //take 
                cur=max(cur,tree_max[st.back()]);
                st.pop_back();
            }
            if(cur>-MX) tree_max[i]= ++cur;
            // else tree_max[i]= -INF
            st.push_back(i);
            ll sz=st.size();

            stack_max[sz]=max(stack_max[sz-1],tree_max[i]);
            dp[1][i]= stack_max[sz];
        }        
        swap(dp[0], dp[1]);
      }

      cout<<dp[0][n]<<"\n"; 
   }
   return 0;
}