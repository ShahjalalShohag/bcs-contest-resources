#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        bool valid = true;
        
        // Check every possible substring
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int len = j - i + 1;
                
                // Compute the number formed by s[i...j] modulo len
                int mod = 0;
                for (int k = i; k <= j; k++) {
                    mod = (mod * 10 + (s[k] - '0')) % len;
                }
                
                // If not divisible by length, answer is NO
                if (mod != 0) {
                    valid = false;
                }
            }
        }
        
        cout << (valid ? "YES" : "NO") << '\n';
    }
    
    return 0;
}
