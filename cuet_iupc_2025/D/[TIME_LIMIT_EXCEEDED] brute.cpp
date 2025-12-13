#include<bits/stdc++.h>
using namespace std;

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

        if (n > 25) {
            // Too large for brute force
            while (true); // Indicate not solvable by this method
            continue;
        }
        
        long long ans = LLONG_MAX;
        
        // Iterate through all subsets of size >= 2
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) < 2) continue;
            
            int and_val = (1 << 30) - 1;
            int or_val = 0;
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    and_val &= a[i];
                    or_val |= a[i];
                }
            }
            
            long long score = and_val ^ or_val;
            ans = min(ans, score);
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
