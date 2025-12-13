#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];

        while ((int)v.size() > 2) {
            bool removed = false;
            for (int i = 1; i + 1 < (int)v.size(); ++i) {
                if (v[i] > v[i-1] && v[i] > v[i+1]) {
                    v.erase(v.begin() + i); 
                    removed = true;
                    break; 
                }
            }
            if (!removed) break; 
        }

        cout << ((int)v.size() == 2 ? "YES" : "NO") << '\n';
    }
    return 0;
}