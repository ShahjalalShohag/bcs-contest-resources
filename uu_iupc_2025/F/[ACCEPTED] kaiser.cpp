#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while (t--) {
        int n;
        string s;
        cin>>n>>s;
        if(n>=5) cout<<"NO\n";
        else{
            int f=1;
            for(int i=0;i<n;i++){
                for(int j=i;j<n;j++){
                    int x=stoi(s.substr(i,j-i+1));
                    if(x%(j-i+1)){
                        f=0;
                        break;
                    }
                }
                if(!f) break;
            }
            if(f) cout<<"YES\n";
            else cout<<"NO\n";
        } 
    }
}
