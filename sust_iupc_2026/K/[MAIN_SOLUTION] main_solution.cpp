#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;
const int mod = 998244353;

int power(int n, long long k) {
	int ans = 1 % mod;
	while (k) {
		if (k & 1) ans = (long long) ans * n % mod;
		n = (long long) n * n % mod;
		k >>= 1;
	}
	return ans;
}

void solve() {
	ll n;
	int k;
	cin >> n >> k;
	vector<ll> p(k);
	for (auto &x : p) cin >> x;

	ll C = 0;
	for (int mask = 0; mask < (1 << k); mask++) {
		u128 prod = 1;
		bool over = false;
		for (int j = 0; j < k; j++) if (mask >> j & 1) {
      prod *= p[j];
      if (prod > (u128)n) {
        over = true;
        break;
      }
    }
		ll term = over ? 0 : (ll)(n / (ll)prod);
		if (__builtin_popcount(mask) & 1) C -= term;
		else C += term;
	}

	int m;
	cin >> m;
	unordered_map<ll, int> base;
	bool conflict = false;
	ll D = 0;
	for (int i = 0; i < m; i++) {
		ll v;
		int c;
		cin >> v >> c;
		int parity = 0;
		for (int j = 0; j < k; j++) while (v % p[j] == 0) {
      v /= p[j];
      parity ^= 1;
    }
		int b = c ^ parity;
		auto it = base.find(v);
		if (it == base.end()) {
			base[v] = b;
			D++;
		} else if (it->second != b) conflict = true;
	}

	cout << (conflict ? 0 : power(2, C - D)) << "\n";
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
