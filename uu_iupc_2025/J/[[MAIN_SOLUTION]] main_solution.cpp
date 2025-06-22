#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> A(n);
        for (int i = 0; i < n; ++i) cin >> A[i];
 
        long long ans = 0;
        std::vector<int> v;
        for(int i = 0; i < n; i++) {
            if(A[i] != -1) v.push_back(i);
        }
        int n1 = v.size();
        long long hi = 1e9;
        if(n1 == 0) {
            cout << 1LL * n * hi << "\n";
            continue;
        }
        ans = hi * v[0];
        long long cur = A[v[0]] * (v[0] + 1);
        for(int i = 1; i < n1; i++) {
            int gap = v[i] - v[i - 1] - 1;
            ans = max(ans, 1LL * gap * hi + cur);
            if(A[v[i]] >= A[v[i - 1]]) {
                cur += A[v[i]] * (gap + 1);
                continue;
            }
            cur = A[v[i]] * (gap + 1);
        }
        cur += hi * (n - 1 - v[n1 - 1]);
        ans = max(ans, cur);
 
        cout << ans << "\n";
    }
 
    return 0;
}
