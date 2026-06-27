#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
void solve() {
    int n; cin >> n;
 
    vector<int> arr(n);
    
    for (auto &i: arr) cin >> i;
    
    while (arr.size() > 0) {
        if(arr.back() > arr.size()) {
            cout << "NO\n"; return;
        }
        arr.pop_back();
    }
    
    cout << "YES\n";
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
 
    return 0;
 
}
