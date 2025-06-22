#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d1(1, 500);
    int t;
    cin>>t;
    while (t--) {
        int n;
        string s;
        cin>>n>>s;
        std::uniform_int_distribution<> d2(0, n-1);
        int f=1;
        int steps=10000;
        while(steps--){
            int i=d2(gen);
            int len=min(5,min(n-i,d1(gen)));
            int x=stoi(s.substr(i,len));
            if(x%len){
                f=0;
                break;
            }
        }
        if(f) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
