#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using pii = pair<int, int>;
using Node = tuple<ll, int, int, int>;

void solve() {
    int n; cin >> n;

    int m = 2 * n;

    vector<pii> points(m);

    for (auto &[x, y] : points) {
        cin >> x >> y;
    }

    vector<ll> key(m);
    vector<ll> sortedKey(m);
    vector<Node> nodes(m);

    for (int j = 1; j < m; j++) {
        int dx = points[j].first - points[0].first;
        int dy = points[j].second - points[0].second;

        for (int i = 0; i < m; i++) {
            auto [x, y] = points[i];
            key[i] = 1LL * dx * y - 1LL * dy * x;
        }

        sortedKey = key;
        sort(sortedKey.begin(), sortedKey.end());

        bool possible = true;

        for (int i = 0; i < m; i += 2) {
            if (sortedKey[i] != sortedKey[i + 1]) {
                possible = false;
                break;
            }
        }

        if (!possible) {
            continue;
        }

        for (int i = 0; i < m; i++) {
            auto [x, y] = points[i];
            nodes[i] = {key[i], x, y, i + 1};
        }

        sort(nodes.begin(), nodes.end());

        for (int i = 0; i < m; i += 2) {
            cout << get<3>(nodes[i]) << ' '
                 << get<3>(nodes[i + 1]) << '\n';
        }

        return;
    }

    cout << -1 << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}