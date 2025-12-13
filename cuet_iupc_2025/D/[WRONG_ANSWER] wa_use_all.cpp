#include<bits/stdc++.h>
using namespace std;

// WA solution: Doesn't realize the identity (a&b)^(a|b) = a^b
// Tries to use all elements thinking more elements = smaller AND = smaller XOR
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        int and_all = (1 << 30) - 1;
        int or_all = 0;
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            and_all &= a[i];
            or_all |= a[i];
        }
        
        // Wrong: assumes using all elements is optimal
        cout << (and_all ^ or_all) << '\n';
    }
    
    return 0;
}
