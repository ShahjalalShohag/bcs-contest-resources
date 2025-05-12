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
      string s; cin>>s;
      bool chk=1;
      sort(all(s)); 
      for(ll i=1;i<n;i++) chk &= (s[i]!=s[i-1]);

      cout<< (chk ?"YES":"NO")<<endl;
   }
   return 0;
}
/*
2
3
abc
2
aa

Output:
Yes
No
*/
