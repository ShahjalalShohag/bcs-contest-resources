#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 5;
int link[20][MAX];
vector<int> yo(string s, string t){
	int n = s.size();
	s += "#" + t;
	vector<int> z(s.size());
	int r = 0, l = 0;
	for(int i = 1; i < s.size(); i++){
		r = max(r, i);
		z[i] = min(z[i - l], r - i);
		while(i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) z[i]++;
		if(r < i + z[i]){
			r = i + z[i];
			l = i;
		}
	}
	vector<int> ret;
	for(int i = n + 1; i < s.size(); i++) ret.push_back(z[i]);
	return ret;
};
void solve(){
	int n, q;
	cin >> n >> q;
	string a, b;
	cin >> a >> b;

	vector<long long> c(n), cum_sum(n);
	for(auto &x: c) cin >> x;

	for(int i = 1; i < n; i++){
		int cur = link[0][i - 1];
		while(~cur && a[cur + 1] != a[i]) cur = link[0][cur];
		link[0][i] = a[cur + 1] == a[i] ? cur + 1 : -1;
		for(int j = 1; j < 20; j++) link[j][i] = (~link[j - 1][i]) ? link[j - 1][link[j - 1][i]] : -1;
	}
	
	vector<vector<pair<int,int>>> query_l(n);
	for(int i = 0; i < q; i++){
		int l, r;
		cin >> l >> r;
		l--, r--;
		query_l[r].push_back({l, i});
	}

	vector<long long> ans(q);
	vector<int> z = yo(a, b);

	int cur_node = -1;

	for(int i = 0; i < n; i++){
		cum_sum[i] = c[i];
		if(~link[0][i]){
			cum_sum[i] += cum_sum[link[0][i]];
		}
	}

	for(int r = 0; r < n; r++){
		while(cur_node != -1 && b[r] != a[cur_node + 1]){
			cur_node = link[0][cur_node];
		}

		if(cur_node + 1 < n && a[cur_node + 1] == b[r]) cur_node++;

		for(auto [l, id] : query_l[r]){
			int len = r - l + 1;

			int low = max(1, len - z[l]);
			int high = len - 1;

			if(low > high || cur_node == -1){
				ans[id] = 0;
				continue;
			}

			int rb = cur_node;

			for(int j = 19; j >= 0; j--){
				if(~rb && ~link[j][rb] && link[j][rb] + 1 > high){
					rb = link[j][rb];
				}
			}

			if(~rb && rb + 1 > high){
				rb = link[0][rb];
			}

			if(rb == -1 || rb + 1 < low){
				ans[id] = 0;
				continue;
			}

			int lb = rb;

			for(int j = 19; j >= 0; j--){
				if(~lb && ~link[j][lb] && link[j][lb] + 1 >= low){
					lb = link[j][lb];
				}
			}

			lb = link[0][lb];

			ans[id] = cum_sum[rb] - (~lb ? cum_sum[lb] : 0);
		}
	}

	for(auto x : ans){
		cout << x << '\n';
	}
}

int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	cin >> t;
	memset(link, -1, sizeof link);
	while(t--) solve();
}


