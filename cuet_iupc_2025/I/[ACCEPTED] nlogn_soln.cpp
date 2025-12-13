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
        vector<int> p(n+1), pos(n+1);
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
            pos[p[i]] = i;
        }

        set<int> alive;
        for (int i = 1; i <= n; ++i) alive.insert(i);

        for (int v = n; v >= 3; --v) {
            int idx = pos[v];
            auto it = alive.find(idx);
            if (it == alive.end()) continue;
            if (it == alive.begin()) continue;
            auto itr = next(it);
            if (itr == alive.end()) continue;
            auto itl = prev(it);
            int L = *itl, R = *itr;
            if (p[idx] > p[L] && p[idx] > p[R]) alive.erase(it);
        }

        cout << (alive.size() == 2 ? "YES\n" : "NO\n");
    }
    return 0;
}
