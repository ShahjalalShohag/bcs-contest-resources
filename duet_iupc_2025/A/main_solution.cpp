#include <bits/stdc++.h>
using namespace std;

const int N = 404;
int mod = 998244353;

int n;
pair<int, int> dp[N][N][N];
bool vis[N][N][N];

pair<int, int> yo(int total_open, int scorable_open, int total_close) {
	if (total_open == n and total_close == n and scorable_open == 0) return {1, 0};
	if (vis[total_open][scorable_open][total_close]) return dp[total_open][scorable_open][total_close];
	vis[total_open][scorable_open][total_close] = true;

	int ways = 0, score = 0;

	if (total_open < n) {
		int remaining = n - total_open;
		auto res = yo(total_open + 1, scorable_open + 1, total_close);
		ways = (ways + 1LL * remaining * res.first) % mod;
		score = (score + 1LL * remaining * res.second) % mod;
	}

	if (scorable_open > 0 and total_close < n) {
		auto res = yo(total_open, 0, total_close + 1);
		ways = (ways + 1LL * scorable_open * res.first) % mod;
		score = (score + 1LL * scorable_open * (res.second + res.first)) % mod;
	}

	if (total_close < n) {
		int non_scorable = total_open - total_close - scorable_open;
		if (non_scorable > 0) {
			auto res = yo(total_open, scorable_open, total_close + 1);
			ways = (ways + 1LL * non_scorable * res.first) % mod;
			score = (score + 1LL * non_scorable * res.second) % mod;
		}
	}

	dp[total_open][scorable_open][total_close] = {ways, score};
	return {ways, score};
}

void solve() {
	cin >> n >> mod;
	auto res = yo(0, 0, 0);
	cout << res.second << '\n';
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                vis[i][j][k]=0;
            }
        }
    }
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    memset(vis,0,sizeof(vis));
    int t;
	cin >> t;
	while (t--) {
		solve();
	}
}