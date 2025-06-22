#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll BIG = 1000000000LL;

void solve() {
    int n; cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int cnt = 0, max_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) cnt++;
        else cnt = 0;
        max_cnt = max(max_cnt, cnt);
    }

    ll answer = max_cnt * BIG;
    
    if (max_cnt == n) {
        cout << answer << "\n";
        return;
    }

    vector<int> knownPos;
    vector<ll> knownVal;

    for (int i = 0; i < n; i++) {
        if (a[i] != -1) {
            knownPos.push_back(i);
            knownVal.push_back(a[i]);
        }
    }

    int m = (int)knownPos.size();
    vector<ll> prefixKnown(m + 1, 0LL), gapWeighted(m, 0LL);
    for (int i = 0; i < m; i++) {
        prefixKnown[i + 1] = prefixKnown[i] + knownVal[i];
    }
    for (int i = 1; i < m; i++) {
        int gapLen = knownPos[i] - knownPos[i - 1] - 1;
        gapWeighted[i] = gapWeighted[i - 1] + gapLen * knownVal[i];
    }

    int idx = 0;
    while (idx < m) {
        int runStart = idx;
        while (idx + 1 < m && knownVal[idx] <= knownVal[idx + 1]) {
            idx++;
        }
        int runEnd = idx;
        idx++;

        ll bestA = LLONG_MIN;
        for (int i = runStart; i <= runEnd; i++) {
            ll LBi = (i == 0 ? 0LL : knownPos[i - 1] + 1LL);
            ll RBi = (i == m - 1 ? (n - 1) : knownPos[i + 1] - 1LL);

            ll pi = knownPos[i];
            ll vi = knownVal[i];

            ll Ai = - prefixKnown[i] - gapWeighted[i] + (pi - LBi) * vi;
            bestA = max(bestA, Ai);

            ll Bi = prefixKnown[i + 1] + gapWeighted[i] + (RBi - pi) * BIG;

            ll candidate = bestA + Bi;
            answer = max(answer, candidate);
        }
    }

    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
