#include<bits/stdc++.h>
using namespace std;

#define MAX 1000000000

typedef long long ll;

ll score[300005];

void solve() {
    int n; cin >> n;
    vector<int> v(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        score[i] = 0;
    }
    v[n] = 0;
    score[n] = 0;

    for(int i = n - 1; i >= 0; i--) {
        if(v[i] == -1) {
            ll nxt_s = v[i + 1] + score[i + 1];
            ll max_s = MAX;

            if(nxt_s >= max_s) {
                score[i] = nxt_s;
                v[i] = v[i + 1];
            } else {
                score[i] = max_s;
                v[i] = MAX;
            }
        }
        else if(v[i] <= v[i + 1]) {
            score[i] = score[i + 1] + v[i];
        } else {
            score[i] = v[i];
        }
    }
    ll mx = 0;
    for(int i = 0; i < n; i++) {
        mx = max(mx, score[i]);
    }

    cout << mx << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}