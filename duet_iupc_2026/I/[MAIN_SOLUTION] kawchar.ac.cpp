#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 1000005

typedef long long ll;
typedef pair<int, int> pii;

void solve() {
    int n; cin >> n;

    vector<pii> boards(n), colors(n);

    for (int i = 0; i < n; i++) {
        cin >> boards[i].first;
        boards[i].second = i;
    }

    for (int j = 0; j < n; j++) {
        cin >> colors[j].first;
        colors[j].second = j;
    }

    sort(boards.begin(), boards.end());

    sort(colors.begin(), colors.end(), [](const pii& a, const pii& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    vector<vector<int>> ans(n, vector<int>(n, 0));

    int i = 0, j = 0;

    while (i < n && j < n) {
        int take = min(boards[i].first, colors[j].first);

        int board_id = boards[i].second;
        int color_id = colors[j].second;

        ans[board_id][color_id] = take;

        boards[i].first -= take;
        colors[j].first -= take;

        if (boards[i].first == 0) i++;
        if (colors[j].first == 0) j++;
    }

    for (int r = 0; r < n; r++) {
        for (int col = 0; col < n; col++) {
            cout << ans[r][col] << " \n"[col + 1 == n];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << boards[i].second + 1 << " \n"[i + 1 == n];
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        solve();
    }

    return 0;
}