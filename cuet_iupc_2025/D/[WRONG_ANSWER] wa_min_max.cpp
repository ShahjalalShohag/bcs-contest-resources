#include<bits/stdc++.h>
using namespace std;

// WA solution: Only checks min and max elements
// Thinks minimizing AND and maximizing OR separately is good
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
        
        int mn = *min_element(a.begin(), a.end());
        int mx = *max_element(a.begin(), a.end());
        
        // Wrong: only considers min and max
        cout << (mn ^ mx) << '\n';
    }
    
    return 0;
}
