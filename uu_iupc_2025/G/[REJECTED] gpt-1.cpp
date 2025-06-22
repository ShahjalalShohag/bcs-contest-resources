#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> A(n);
        for (int &x : A) cin >> x;

        long long ans = 0;
        vector<int> freq(n + 2, 0); // max possible value of MEX = n+1

        for (int i = 0; i < n; ++i) {
            int mex = 0;
            int curr_max = -1;
            fill(freq.begin(), freq.begin() + n + 2, 0); // reset frequency for this i

            for (int j = i; j < n; ++j) {
                curr_max = max(curr_max, A[j]);
                freq[curr_max]++;

                // simulate prefix max array — we only add prefix max values
                // So we add to MEX tracking only the curr_max
                while (freq[mex] > 0) ++mex;

                ans += mex;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
