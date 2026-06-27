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

        priority_queue<pair<long long,int>> pq;

        for (int i = 1; i <= n; i++) {
            long long x;
            cin >> x;
            pq.push({x, i});
        }

        while (!pq.empty()) {
            auto [val, pos] = pq.top();

            if (val <= pos) {
                pq.pop();
            } else {
                break;
            }
        }

        cout << (pq.empty() ? "YES" : "NO") << '\n';
    }

    return 0;
}