#include "bits/stdc++.h"
using namespace std;

int n, mod;
int mem[2][401][401][401];

long long dp(int cur, int before, int after, int taken) {
    if(before < 0 || after < 0 || cur + before + after > n || before + after > 2 * (n - cur)) {
        return 0;
    }
    if(cur == n) {
        return (before == 0 && after == 0 && taken);
    }
    if(mem[taken][cur][before][after] != -1) {
        return mem[taken][cur][before][after];
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
    return mem[taken][cur][before][after] = ans % mod;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> mod;
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k <= n; k++) {
                    mem[0][i][j][k] = -1;
                    mem[1][i][j][k] = -1;
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