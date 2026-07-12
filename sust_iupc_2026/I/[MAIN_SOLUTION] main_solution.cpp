#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;

int K;
vector<array<int, 2>> ch;
vector<int> cnt;

int new_node() {
	ch.push_back({-1, -1});
	cnt.push_back(0);
	return (int)ch.size() - 1;
}

void insert(ll x) {
	int u = 0;
	for (int b = K - 1; b >= 0; b--) {
		int bit = (x >> b) & 1;
		if (ch[u][bit] == -1) ch[u][bit] = new_node();
		u = ch[u][bit];
		cnt[u]++;
	}
}

// smallest v >= 0 with (base ^ v) not yet inserted
ll query(ll base) {
	int u = 0;
	ll v = 0;
	for (int b = K - 1; b >= 0; b--) {
		int want = (base >> b) & 1;
		int c = ch[u][want];
		ll full = 1LL << b;
		int take = (c == -1 || cnt[c] < full) ? want : (want ^ 1);
		if (take != want) v |= 1LL << b;
		if (ch[u][take] == -1) return v;
		u = ch[u][take];
	}
	return v;
}

void solve() {
	int n;
	ll k;
	cin >> n >> k;
	vector<ll> a(n);
	for (auto &x : a) cin >> x;

	ll P = 1LL << k;
	ll ways = 1;
	bool feasible = true;
	for (int i = 1; i <= n; i++) {
		ll term = P - i;
		if (term <= 0) {
			feasible = false;
			break;
		}
		ways = ways * (term % MOD) % MOD;
	}
	if (!feasible) {
		cout << 0 << '\n';
		return;
	}
	cout << ways << '\n';

	K = (k == 0) ? 1 : (int)k;
	ch.clear();
	cnt.clear();
	new_node(); // root
	insert(0);
	ll c_prev = 0;
	for (int i = 0; i < n; i++) {
		ll base = c_prev ^ a[i];
		ll v = query(base);
		ll c_i = base ^ v;
		insert(c_i);
		c_prev = c_i;
		cout << v << " \n"[i + 1 == n];
	}
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
