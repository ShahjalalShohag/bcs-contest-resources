#include<bits/stdc++.h>
using namespace std;

// WA solution: Initial ans is not large enough (uses 1e9 but max XOR can be ~2e9)
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        sort(a.begin(), a.end());
        
        int ans = 1e9; // Wrong: max XOR of two 10^9 numbers can be up to ~2*10^9
        for (int i = 0; i < n - 1; i++) {
            int score = a[i] ^ a[i + 1];
            ans = min(ans, score);
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
