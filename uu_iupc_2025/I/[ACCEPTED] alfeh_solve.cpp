#include<bits/stdc++.h>
using namespace std;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        bool ok = true;
        for(int i = 0; i + 1 < n; i++) {
            if(s[i] == s[i + 1] && s[i] == 'B') 
                ok = false;
        }
        if(!ok) {
            cout << "-1\n";
            continue;
        }
        std::vector<int> b;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'B') b.push_back(i);
        }
        int a = b.size();
        if(!a) {
            cout << "-1\n";
            continue;
        }
        std::vector<int> ans(n);
        int bb = 0;
        int first_b = 0;
        while(s[first_b] == 'A') first_b++;
        int j = first_b - 1;
        while(j >= 0) ans[j--] = ++a;
        for(int i = first_b; i < n; i++) {
            if(s[i] == 'A') ans[i] = ++a;
            else ans[i] = ++bb;
        }
        for(int i = 0; i < n; i++) {
            cout << ans[i] << " \n"[i + 1 == n]; 
        }
    }
    return 0;
}
