#include "bits/stdc++.h"
using namespace std;

const int MAXN = 100 + 5;
int MOD = 998244353;

vector<vector<vector<int>>> dp,adp;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        scanf("%d", &MOD);
        int len = 2 * n;

        dp.assign(len+5,vector<vector<int>>(len+5,vector<int>(len+5,0)));
        dp[0][0][n] = 1;

        for (int i = 1; i <= len; ++i) {
            adp.assign(len+5,vector<vector<int>>(len+5,vector<int>(len+5,0)));
            for (int score = 0; score < i; ++score) {
                for (int open = 0; open < i; ++open) {
                    for (int rem = 0; rem <= n; ++rem) {
                        int val = dp[score][open][rem];
                        if (val == 0) continue;
                        if (open >= 1) adp[score + 1][0][rem] = (adp[score + 1][0][rem] + 1LL * val * open % MOD) % MOD;
                        if (rem >= 1) adp[score][open + 1][rem - 1] = (adp[score][open + 1][rem - 1] + 1LL * val * rem % MOD) % MOD;
                        int not_affect = len - i + 1 - 2 * rem - open;
                        if (not_affect >= 1) adp[score][open][rem] = (adp[score][open][rem] + 1LL * val * not_affect % MOD) % MOD;
                    }
                }
            }

            for (int x = 0; x <= len; ++x)
                for (int y = 0; y <= len; ++y)
                    for (int z = 0; z <= n; ++z)
                        dp[x][y][z] = adp[x][y][z];
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) ans = (ans + 1LL * i * dp[i][0][0] % MOD) % MOD;
        printf("%d\n", ans);
        for(int i=0;i<=len;i++){
            for(int j=0;j<=len;j++){
                for(int k=0;k<=len;k++){
                    dp[i][j][k]=0;
                }
            }
        }
    }

}
