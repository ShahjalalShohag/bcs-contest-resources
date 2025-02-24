#include<bits/stdc++.h>
using namespace std;


void solve(){
	int n, q;
	cin >> n >> q;
	n *= 2;
	vector<int> s(n);
	for (int i = 0; i < n; i++) cin >> s[i];
	vector<int> cum_sum(n + 1);
	for(int i = 1; i < n; i++){
		cum_sum[i] += cum_sum[i - 1] + (s[i - 1] == -s[i]);
	}
	cum_sum[n] = cum_sum[n - 1];
	for(int i = 0; i < q; i++){
		int l, r;
		cin >> l >> r;
		cout << cum_sum[r] - cum_sum[l - 1] << '\n';
	}
}

int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
}