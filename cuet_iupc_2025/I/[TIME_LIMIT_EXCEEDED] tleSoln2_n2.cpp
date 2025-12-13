#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; 
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];

        for (int target = n; target >= 3; --target) {
            int pos = -1;
            for (int i = 0; i < (int)v.size(); ++i) {
                if (v[i] == target) {
                    pos = i;
                    break;
                }
            }
            if (pos == -1) continue;
            if (pos > 0 && pos + 1 < (int)v.size() && v[pos] > v[pos-1] && v[pos] > v[pos+1]) {
                v.erase(v.begin() + pos);
            }
        }

        cout << ((int)v.size() == 2 ? "YES\n" : "NO\n");
    }

    return 0;
}
