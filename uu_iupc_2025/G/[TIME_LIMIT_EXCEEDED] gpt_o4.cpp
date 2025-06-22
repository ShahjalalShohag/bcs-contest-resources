#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) 
            cin >> a[i];

        deque<pair<int,int>> dq; // (value, position)
        ll ans = 0;
        // build from right to left
        for (int L = n - 1; L >= 0; --L) {
            // remove any old records ≤ a[L]
            while (!dq.empty() && dq.front().first <= a[L]) 
                dq.pop_front();
            // insert the new record at the front
            dq.push_front({a[L], L});

            // scan the deque’s head: as long as dq[i].first == i,
            // that record injects +1 into the beauty for every R >= dq[i].second
            for (int i = 0; i < (int)dq.size(); ++i) {
                if (dq[i].first != i) 
                    break;
                ans += (n - dq[i].second);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
