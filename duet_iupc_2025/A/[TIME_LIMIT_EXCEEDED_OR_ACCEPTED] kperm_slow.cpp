#include "bits/stdc++.h"
using namespace std;

int n, mod;
int mem[401][401][401][2];

long long dp(int cur, int before, int after, int taken) {
    if(before < 0 || after < 0 || before + after > n) {
        return 0;
    }
    if(cur == n) {
        return (before == 0 && after == 0 && taken);
    }
    if(mem[cur][before][after][taken] != -1) {
        return mem[cur][before][after][taken];
    }
    long long ans = 0;
    ans += dp(cur, before, after + 1, taken);
    ans += before * dp(cur + 1, before - 1, after, taken);
    if(taken == 0) {
        ans += after * dp(cur + 1, before + after - 1, 0, 0);
        ans += after * dp(cur + 1, before + after - 1, 0, 1);
    } else {
        ans += after * dp(cur + 1, before + after - 1, 0, 1);
    }
    return mem[cur][before][after][taken] = ans % mod;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> mod;
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k <= n; k++) {
                    mem[i][j][k][0] = -1;
                    mem[i][j][k][1] = -1;
                }
            }
        }
        auto ans = dp(0, 0, 0, 0);
        for(int i = 1; i <= n; i++) {
            ans = (ans * i) % mod;
        }
        cout << ans << endl;
    }
}