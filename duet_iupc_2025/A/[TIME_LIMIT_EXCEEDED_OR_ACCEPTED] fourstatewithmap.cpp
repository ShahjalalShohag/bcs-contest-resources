#include "bits/stdc++.h"
using namespace std;

int MOD = 998244353;

int n;      
int len;    
map<tuple<int, int, int, int>, int> dp;

int solve(int i, int score, int open, int rem) {
    if (i == len)  return (open == 0 && rem == 0) ? score : 0;
    auto state = make_tuple(i, score, open, rem);
    if (dp.count(state)) return dp[state];
    long long total_score_sum = 0;
    if (open >= 1) total_score_sum = (total_score_sum + 1LL * open * solve(i + 1, score + 1, 0, rem)) % MOD;
    if (rem >= 1) total_score_sum = (total_score_sum + 1LL * rem * solve(i + 1, score, open + 1, rem - 1)) % MOD;
    int not_affect = len - i - 2 * rem - open;
    if (not_affect >= 1) total_score_sum = (total_score_sum + 1LL * not_affect * solve(i + 1, score, open, rem)) % MOD;
    return dp[state] = (int)total_score_sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >>MOD;
        len = 2 * n; 
        dp.clear();
        int ans = solve(0, 0, 0, n);
        cout << ans << "\n";
    }
}