#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        
        string a, b;
        cin >> a >> b;
        
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--; r--; // Convert to 0-indexed
            
            string c = b.substr(l, r - l + 1);
            int len = c.length();
            int answer = 0;
            
            // For each possible k from 1 to length of c
            for (int k = 1; k <= len; k++) {
                bool valid = true;
                
                // Check if all k-length substrings of c exist in a
                for (int i = 0; i <= len - k; i++) {
                    string substr = c.substr(i, k);
                    
                    // Check if this substring exists in a
                    if (a.find(substr) == string::npos) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    answer++;
                }
            }
            
            cout << answer << "\n";
        }
    }
    
    return 0;
}
