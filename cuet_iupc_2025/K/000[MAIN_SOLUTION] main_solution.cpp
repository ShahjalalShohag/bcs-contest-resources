#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, mod = 998244353;
using ll = long long;

vector<int> g[N];
int sz[N], inv[N];
int n, tot_inv_prod;

int power(int n, long long k) {
	int ans = 1 % mod;
	while (k) {
		if (k & 1) ans = (long long) ans * n % mod;
		n = (long long) n * n % mod;
		k >>= 1;
	}
	return ans;
}

void prec() {
	for (int i = 1; i < N; i++) {
		inv[i] = power(i, mod - 2);
	}
}

void dfs1(int u, int p = 0) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v == p) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

void dfs2(int u, int p, int cur) {
	tot_inv_prod = (tot_inv_prod + cur) % mod;
	for (auto v : g[u]) {
		if (v == p) continue;
		int nxt = 1LL * cur * sz[v] % mod * inv[n - sz[v]] % mod;
		dfs2(v, u, nxt);
	}
}

void solve() {
	int k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) g[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	// If k < n - 1, we cannot assign distinct weights
	if (k < n - 1) {
		cout << 0 << '\n';
		return;
	}

	dfs1(1);

	int cur = 1;
	for (int i = 2; i <= n; i++) {
		cur = 1LL * cur * inv[sz[i]] % mod;
	}

	tot_inv_prod = 0;
	dfs2(1, 0, cur);

	// C(k + 1, n) = (k+1) * k * ... * (k+1 - n + 1)
	int ways = 1;
	for (int i = 0; i < n; i++) {
		ways = 1LL * ways * ((k + 1 - i) % mod) % mod;
	}

	int ans = 1LL * tot_inv_prod * ways % mod;
	ans = 1LL * ans * inv[n] % mod;
	ans = 1LL * ans * inv[2] % mod;

	cout << ans << '\n';
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	prec();
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}