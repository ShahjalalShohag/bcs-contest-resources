#include <bits/stdc++.h>
using namespace std;
int MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n >> MOD;
        // WARNING: brute force is O(((2n)!/2^n) * n log n).
        // Feasible only for n up to 6.
        vector<int> a(2*n);
        for(int i = 0; i < n; i++){
            a[2*i] = a[2*i+1] = i;
        }
        sort(a.begin(), a.end());

        long long ans = 0;
        do {
            static int L[400], R[400];
            for(int i = 0; i < n; i++){
                L[i] = R[i] = -1;
            }
            for(int i = 0; i < 2*n; i++){
                int v = a[i];
                if(L[v] == -1) L[v] = i;
                else R[v] = i;
            }
            vector<pair<int,int>> iv(n);
            for(int i = 0; i < n; i++){
                iv[i] = {R[i], L[i]};
            }
            sort(iv.begin(), iv.end());
            int cnt = 0, last_end = -1;
            for(auto &p : iv){
                int st = p.second, ed = p.first;
                if(st > last_end){
                    cnt++;
                    last_end = ed;
                }
            }
            ans += cnt;
            if(ans >= MOD) ans -= MOD;
        } while(next_permutation(a.begin(), a.end()));

        cout << ans % MOD << "\n";
    }
    return 0;
}