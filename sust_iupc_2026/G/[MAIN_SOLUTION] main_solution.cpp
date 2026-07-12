#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 998244353;
using ll = long long;

vector<int> g[N];
// down = matched to a child, up = matched to its parent, fre = unmatched.
ll down[N], up[N], fre[N];

void dfs(int u, int p) {
	ll d = 0, prod_s = 1, prod_m = 1;
	for (int v : g[u]) {
		if (v == p) continue;
		dfs(v, u);
		ll s = (down[v] + fre[v]) % mod;
		d = (d * s + prod_s * up[v]) % mod;
		prod_s = prod_s * s % mod;
		prod_m = prod_m * down[v] % mod;
	}
	down[u] = d;
	up[u] = prod_s;
	fre[u] = prod_m;
}

void solve() {
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	cout << (down[1] + fre[1]) % mod << '\n';
	for (int i = 1; i <= n; i++) g[i].clear();
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
