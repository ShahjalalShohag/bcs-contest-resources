#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    int tc;
    cin >> tc;
    for(int cs = 1; cs <= tc; cs++){
        int n;
        cin >> n;
        
        string s;
        cin >> s;
        
        bool hasB = any_of(s.begin(), s.end(), [](char c) { 
            return c == 'B'; 
        });
        if(!hasB) {
            cout << -1 << '\n';
            continue;
        }

        bool consecutiveB = adjacent_find(s.begin(), s.end(), [](char a, char b) { 
            return a == 'B' && b == 'B'; 
        }) != s.end();
        if (consecutiveB) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> ans(n);
        iota(ans.rbegin(), ans.rend(), 1); // Fill with n to 1

        for(int i = 0; i < n; i++) {
            auto it = find(s.rbegin() + i, s.rend(), 'B');
            if (it == s.rend()) {
                break;
            }
            int j = it - s.rbegin();
            reverse(ans.rbegin() + i, ans.rbegin() + j + 1);
            i = j;
        }

        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << ' ';
        }

        cout << '\n';
    }
}