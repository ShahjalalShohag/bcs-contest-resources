#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
const ll N= 1e5+5;
 
int main(){
   FastIO;
 
   string s; cin>>s;
   ll n= s.size(),ans= 1e18;
   set<ll> stt;
   assert(n>=3 && n<=100000);

   for(ll i=0;i<n;i++){
     if(i<n-1) assert(s[i]!=s[i+1]);
     stt.insert(s[i]);
     assert(s[i]=='a' || s[i]=='b' || s[i]=='c');
 
     set<char> st;
     for(ll j=i;j<min(n,i+100LL);j++){
        st.insert((char)s[j]);
        if((ll)st.size()==3){
            ans= min(ans,j-i+1);
            break;
        }
     }
   }

   assert((ll)stt.size()==3);
 
   cout<<ans<<endl;
   
 
   return 0;
}
/*
 
*/
