#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Iterate through all n^k sequences
        // Each sequence is represented by k indices in [0, n-1]
        vector<int> idx(k, 0);
        long long ans = 0;
        
        while (true) {
            // Compute contribution of current sequence
            int t_val = a[idx[0]];
            for (int i = 1; i < k; i++) {
                t_val = t_val / a[idx[i]];
            }
            ans = (ans + t_val) % mod;
            
            // Move to next sequence
            int pos = k - 1;
            while (pos >= 0 && idx[pos] == n - 1) {
                idx[pos] = 0;
                pos--;
            }
            if (pos < 0) break;
            idx[pos]++;
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}

