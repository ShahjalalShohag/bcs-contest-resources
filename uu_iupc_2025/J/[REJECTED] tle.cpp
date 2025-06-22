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
        long long hi = 1e9;
        for(int i = 0; i < n; i++) {
          
          long long sum = 0;
          int j = i;
          std::vector<int> v;
          int last_val = 0;
          for(; j < n; j++) {
            if(A[j] != -1 && A[j] < last_val) break;
            if(A[j] != -1) last_val = A[j], v.push_back(j);
          }
          int i1 = i - 1;
          for(int &u:v) {
            sum += 1LL * (u - i1) * A[u];
            ans = max(ans, 1LL * (u - i1 - 1) * hi);
            i1 = u;
          }
          sum += 1LL * (j - i1 - 1) * hi;
          ans = max(ans, sum);

          // cout << sum << "\n";
        }
        
        cout << ans << "\n";
    }
 
    return 0;
}
