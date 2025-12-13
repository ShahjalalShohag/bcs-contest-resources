#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long power(long long a, long long b) {
	a %= MOD;
	if (a < 0) a += MOD;
	long long res = 1;
	while (b > 0) {
		if (b & 1) res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

long long modinv(long long a) {
	return power(a, MOD - 2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--) {
		int n;
		long long k;
		cin >> n >> k;

		vector<int> a(n);
		int M = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			M = max(M, a[i]);
		}

		// Count occurrences
		vector<long long> cnt(M + 1, 0);
		for (int i = 0; i < n; i++) {
			cnt[a[i]]++;
		}

		long long cnt1 = cnt[1];

		// Compute maximum depth D = ceil(log2(M))
		// After D divisions by elements >= 2, any value becomes 0
		int D = 0;
		for (int temp = M; temp > 0; temp /= 2) D++;
		D = min((long long)D, k - 1);

		// G[v] = sum over all d-length sequences of non-1 elements of final value starting from v
		vector<long long> G(M + 1);
		for (int v = 0; v <= M; v++) {
			G[v] = v;  // G(v, 0) = v
		}

		// F[d] = sum_v cnt[v] * G(v, d)
		vector<long long> F(D + 1, 0);
		for (int v = 1; v <= M; v++) {
			F[0] = (F[0] + cnt[v] * v) % MOD;
		}

		// Compute G(v, d) for d = 1 to D using range addition
		for (int d = 1; d <= D; d++) {
			vector<long long> diff(M + 2, 0);

			// For each non-1 element y, contribute to the transition
			for (int y = 2; y <= M; y++) {
				if (cnt[y] == 0) continue;

				// floor(v/y) = q for v in [q*y, (q+1)*y - 1]
				for (int q = 0; q * y <= M; q++) {
					int l = max(1, q * y);
					int r = min(M, (q + 1) * y - 1);
					if (l > r) continue;

					long long val = cnt[y] * G[q] % MOD;
					diff[l] = (diff[l] + val) % MOD;
					diff[r + 1] = (diff[r + 1] - val % MOD + MOD) % MOD;
				}
			}

			// Reconstruct G from difference array
			long long psum = 0;
			for (int v = 1; v <= M; v++) {
				psum = (psum + diff[v]) % MOD;
				G[v] = psum;
			}
			G[0] = 0;

			// Compute F[d]
			for (int v = 1; v <= M; v++) {
				F[d] = (F[d] + cnt[v] * G[v]) % MOD;
			}
		}

		// Compute the answer:
		// ans = sum_{d=0}^{D} C(k-1, d) * cnt1^{k-1-d} * F[d]
		// where d = number of non-1 divisions among positions 2 to k
		long long ans = 0;

		// Precompute factorials
		vector<long long> fact(D + 2, 1);
		for (int i = 1; i <= D + 1; i++) {
			fact[i] = fact[i - 1] * i % MOD;
		}

		for (int d = 0; d <= D; d++) {
			// C(k-1, d) = (k-1) * (k-2) * ... * (k-d) / d!
			long long binom = 1;
			for (int i = 0; i < d; i++) {
				binom = binom * ((k - 1 - i) % MOD) % MOD;
			}
			binom = binom * modinv(fact[d]) % MOD;

			// cnt1^{k-1-d}
			long long pw;
			if (cnt1 == 0 && k - 1 - d > 0) {
				pw = 0;  // 0^positive = 0
			} else {
				pw = power(cnt1, k - 1 - d);  // handles 0^0 = 1
			}

			ans = (ans + binom * pw % MOD * F[d]) % MOD;
		}

		cout << ans << '\n';
	}

	return 0;
}

