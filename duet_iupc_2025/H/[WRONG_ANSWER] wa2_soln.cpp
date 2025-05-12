#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define FastIO ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const ll MAX_N = 3e5 + 5;

int main() {
    FastIO;
    ll T;
    cin >> T;

    while (T--) {
        ll n;
        cin >> n;
        string s;
        cin >> s;

        ll aa = 0, bb = 0, ss = 0;
        
        for (ll i = 0; i < n; i++) {
            if (s[i] == 'A') aa++;
            if (s[i] == 'B') bb++;
            if (s[i] == 'S') ss++;
        }
        
        if (aa == n || bb == n) {
            cout << 1 << endl;
        } 
        else if (aa > 0 && bb > 0) {
            cout << 2 << endl;
        } 
        else if (ss == n) {
            cout << 1 << endl;  
        } 
        else {
            cout << 2 << endl;
        }
    }

    return 0;
}
