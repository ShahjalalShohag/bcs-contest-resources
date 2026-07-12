#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n + 1);
        for (int x = 1; x <= n; x++) scanf("%d", &a[x]);
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            cnt[v]++;
        }

        // pref[x] = number of indices whose demanded value lies at positions 1..x
        vector<long long> pref(n + 1, 0);
        for (int x = 1; x <= n; x++) pref[x] = pref[x - 1] + cnt[a[x]];

        // nearest strictly-greater neighbours of each position
        vector<int> L(n + 1), R(n + 2);
        vector<int> st;
        st.reserve(n);
        for (int x = 1; x <= n; x++) {
            while (!st.empty() && a[st.back()] < a[x]) st.pop_back();
            L[x] = st.empty() ? 0 : st.back();
            st.push_back(x);
        }
        st.clear();
        for (int x = n; x >= 1; x--) {
            while (!st.empty() && a[st.back()] < a[x]) st.pop_back();
            R[x] = st.empty() ? n + 1 : st.back();
            st.push_back(x);
        }

        long long ans = 1;
        for (int x = 1; x <= n && ans; x++) {
            int v = a[x];
            if (!cnt[v]) continue;
            long long sz = R[x] - L[x] - 1;                 // positions in v's range
            long long T = pref[R[x] - 1] - pref[L[x]] - cnt[v]; // slots taken by smaller values
            long long base = sz - T;
            for (int k = 0; k < cnt[v]; k++) {
                long long f = base - k;
                if (f <= 0) { ans = 0; break; }
                ans = ans * (f % MOD) % MOD;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
