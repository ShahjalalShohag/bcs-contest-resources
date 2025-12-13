#include<bits/stdc++.h>
using namespace std;

// TLE solution: O(n^2) - checks all pairs without sorting optimization
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
        
        int ans = INT_MAX;
        
        // Check all pairs - O(n^2)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int score = a[i] ^ a[j];
                ans = min(ans, score);
            }
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
