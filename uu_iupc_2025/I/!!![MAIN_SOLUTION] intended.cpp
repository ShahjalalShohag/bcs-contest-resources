#include <algorithm>
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

        vector<int> ans(s.size());
        iota(ans.begin(), ans.end(), 1);

        for(int i = 0; i < s.size(); i++) {
            auto it = find(s.begin() + i, s.end(), 'B');
            if (it == s.end()) {
                break;
            }
            int j = it - s.begin();
            reverse(ans.begin() + i, ans.begin() + j + 1);
            i = j;
        }

        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << ' ';
        }

        cout << '\n';
    }
}
