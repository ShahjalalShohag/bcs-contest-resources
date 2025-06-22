#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    const ll BIG = 1000000000LL;

    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        // 1) Gather the fixed positions and values.
        vector<int> pos_fixed;
        vector<ll> val_fixed;
        for (int i = 1; i <= n; i++) {
            if (a[i] != -1) {
                pos_fixed.push_back(i);
                val_fixed.push_back(a[i]);
            }
        }
        int m = (int)pos_fixed.size();

        // Special case: no fixed entries at all => best is all -1 => all become 1e9
        if (m == 0) {
            cout << (ll)n * BIG << "\n";
            continue;
        }

        // 2) Build neg_count[1..m+1]:
        //    neg_count[k] = # of -1's between pos_fixed[k-1]+1 .. pos_fixed[k]-1
        vector<ll> neg_count(m+2, 0);
        {
            ll cnt = 0;
            int k = 0;  // index in pos_fixed
            for (int i = 1; i <= n; i++) {
                if (k < m && pos_fixed[k] == i) {
                    // just hit a fixed
                    neg_count[k+1] = cnt;
                    cnt = 0;
                    k++;
                } else {
                    if (a[i] == -1) cnt++;
                }
            }
            // remaining -1's after the last fixed
            neg_count[m+1] = cnt;
        }

        // 3) Prefix sums of fixed values and weighted sums
        vector<ll> pref_fix(m+1, 0), pref_w(m+1, 0);
        for (int i = 1; i <= m; i++) {
            pref_fix[i] = pref_fix[i-1] + val_fixed[i-1];
            pref_w[i]   = pref_w[i-1] + neg_count[i] * val_fixed[i-1];
        }

        // 4) Sweep i=1..n
        ll ans = 0;
        int fR = 0;       // how many fixed we've seen up to i
        int fL = 1;       // the first fixed >= start
        int start = 1;    // earliest allowed start of our segment

        for (int i = 1; i <= n; i++) {
            if (a[i] != -1) {
                // we hit a new fixed
                fR++;
                // check for a "decrease" vs. previous fixed
                if (fR >= 2 && val_fixed[fR-2] > val_fixed[fR-1]) {
                    // must split: start just past the previous fixed
                    start = pos_fixed[fR-2] + 1;
                    // advance fL so that pos_fixed[fL-1] < start <= pos_fixed[fL]
                    while (fL <= m && pos_fixed[fL-1] < start) {
                        fL++;
                    }
                }
            }

            ll best_here;
            if (fL <= fR) {
                // there is at least one fixed in [start..i]
                // sum of those fixed:
                ll sumFix = pref_fix[fR] - pref_fix[fL-1];

                // block before the first fixed in the segment:
                ll c1 = (ll)pos_fixed[fL-1] - start;
                // NB: pos_fixed[fL-1] is the fL-th fixed's position
                ll block1 = c1 * val_fixed[fL-1];

                // blocks between fixed:
                ll blockRest = pref_w[fR] - pref_w[fL];

                // tail of -1's after the last fixed
                ll tail = (ll)(i - pos_fixed[fR-1]) * BIG;

                best_here = sumFix + block1 + blockRest + tail;
            }
            else {
                // no fixed in [start..i] => all are -1
                ll len = (ll)(i - start + 1);
                best_here = len * BIG;
            }

            ans = max(ans, best_here);
        }

        cout << ans << "\n";
    }

    return 0;
}
