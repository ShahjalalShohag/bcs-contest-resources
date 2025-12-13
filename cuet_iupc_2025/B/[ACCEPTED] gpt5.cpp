#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1000000 + 5;
const int LMAX = 25; // > log2(1e6) (~20), safe margin

using ll = long long;

int addmod(int a, int b) {
	int s = a + b;
	if (s >= MOD) s -= MOD;
	return s;
}
int submod(int a, int b) {
	int s = a - b;
	if (s < 0) s += MOD;
	return s;
}
int mulmod(ll a, ll b) {
	return (int)( (a * b) % MOD );
}

int mod_pow(int a, long long e) {
	int r = 1;
	int x = a;
	while (e > 0) {
		if (e & 1) r = mulmod(r, x);
		x = mulmod(x, x);
		e >>= 1;
	}
	return r;
}

int mod_inv(int a) {
	return mod_pow(a, MOD - 2);
}

// global reusable buffers
static int cntArr[MAXN];
static int prefixCnt[MAXN];
static int G[MAXN];          // G[d]
static int prob_prev[MAXN];
static int prob_cur[MAXN];
static int invSmall[LMAX + 1];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// precompute small inverses for 1..LMAX
	for (int i = 1; i <= LMAX; ++i) {
		invSmall[i] = mod_inv(i);
	}

	int T;
	if (!(cin >> T)) return 0;
	while (T--) {
		int n;
		long long k;
		cin >> n >> k;

		// clear counts for this test (only 1..n used across all tests)
		for (int i = 1; i <= n; ++i) cntArr[i] = 0;

		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			cntArr[a[i]]++;
		}

		// basic stats
		int c1 = cntArr[1];              // number of ones
		int c_pos = n - c1;              // number of >1
		int sumA = 0;                    // sum of all a_i
		for (int v = 1; v <= n; ++v) {
			if (cntArr[v] == 0) continue;
			sumA = addmod(sumA, mulmod(v, cntArr[v]));
		}

		if (k == 1) {
			// no denominators: each sequence is just one element
			cout << sumA << "\n";
			continue;
		}

		// all ones: every sequence contributes 1
		if (c1 == n) {
			int base = n % MOD;
			int ans = mod_pow(base, k);  // n^k mod
			cout << ans << "\n";
			continue;
		}

		long long N = k - 1; // number of denominators
		// floor log2(n)
		int L = 0;
		while ((1LL << (L + 1)) <= n) ++L;
		// max t for which product of t non-1s can still be <= n
		long long max_t_ll = min((long long)L, N);
		int max_t = (int)max_t_ll;

		// precompute prefix counts
		prefixCnt[0] = 0;
		for (int v = 1; v <= n; ++v) {
			prefixCnt[v] = prefixCnt[v - 1] + cntArr[v];
		}

		// precompute G[d] = sum_v cnt[v] * floor(v/d)
		for (int d = 1; d <= n; ++d) {
			ll sum = 0;
			int limit = n / d;
			int Lpos = d;
			for (int q = 1; q <= limit; ++q) {
				int Rpos = (q == limit ? n : (q + 1) * d - 1);
				int rangeCnt = prefixCnt[Rpos] - prefixCnt[Lpos - 1];
				if (rangeCnt != 0) {
					sum += (ll)rangeCnt * q;
					if (sum >= (ll)MOD * MOD) sum %= MOD; // avoid overflow
				}
				Lpos += d;
			}
			G[d] = (int)(sum % MOD);
		}

		int n_mod = n % MOD;
		int pow_n_kminus1 = mod_pow(n_mod, k - 1);

		// prepare non-1 values and their conditional probabilities
		vector<int> non1_vals;
		non1_vals.reserve(c_pos);
		for (int v = 2; v <= n; ++v) {
			if (cntArr[v] > 0) non1_vals.push_back(v);
		}

		// we will use distribution over "non-1" values: P_non1(v) = cnt[v] / c_pos
		int inv_cpos = mod_inv(c_pos % MOD);

		// DP for products Z_t of t non-1 picks, for t = 1..max_t
		vector<int> H;      // H[t] = E[ G(Z_t) ]
		H.assign(max_t + 1, 0);

		// Z_0 = 1 with prob 1
		for (int i = 0; i <= n; ++i) prob_prev[i] = 0;
		prob_prev[1] = 1;

		// precompute probabilities for non-1 values
		vector<int> prob_non1;
		prob_non1.reserve(non1_vals.size());
		for (int v : non1_vals) {
			int p = mulmod(cntArr[v], inv_cpos); // cnt[v] / c_pos mod
			prob_non1.push_back(p);
		}

		for (int t = 1; t <= max_t; ++t) {
			// clear prob_cur
			for (int i = 0; i <= n; ++i) prob_cur[i] = 0;

			// convolution: multiply previous product by one non-1 value
			for (size_t idx = 0; idx < non1_vals.size(); ++idx) {
				int v = non1_vals[idx];
				int p_v = prob_non1[idx];
				int max_s = n / v;
				for (int s = 1; s <= max_s; ++s) {
					int pv = prob_prev[s];
					if (pv == 0) continue;
					int d = s * v;
					int add = mulmod(pv, p_v);
					int &ref = prob_cur[d];
					ref += add;
					if (ref >= MOD) ref -= MOD;
				}
			}

			// compute H[t] = sum_d prob_cur[d] * G[d]
			int Ht = 0;
			for (int d = 1; d <= n; ++d) {
				int pd = prob_cur[d];
				if (pd == 0) continue;
				Ht = addmod(Ht, mulmod(pd, G[d]));
			}
			H[t] = Ht;

			// prepare for next t
			for (int i = 0; i <= n; ++i) prob_prev[i] = prob_cur[i];
		}

		int answer = 0;

		// CASE 1: no ones at all
		if (c1 == 0) {
			// all denominators are >1; T = N (deterministic).
			// If N > L, product >= 2^N > n, so contribution is 0.
			if (N > L) {
				answer = 0;
			} else {
				// N <= max_t == N
				int Sbase = H[(int)N]; // only t = N contributes
				answer = mulmod(pow_n_kminus1, Sbase);
			}
			cout << answer << "\n";
			continue;
		}

		// CASE 2: some ones and some >1
		// T ~ Binomial(N, q), where q = P(v > 1) = (n - c1) / n
		int inv_n = mod_inv(n_mod);
		int p1 = mulmod(c1 % MOD, inv_n);            // probability pick = 1
		int q  = mulmod((n - c1) % MOD, inv_n);      // probability pick > 1

		// P_T[0] = p1^N
		int PT0 = mod_pow(p1, N);

		// base sum: t = 0 => all denominators are 1 => t_k = x1
		// contributes sumA
		int Sbase = mulmod(PT0, sumA);

		if (max_t > 0) {
			// compute P_T[t] for t = 1..max_t via recurrence
			int inv_p1 = mod_inv(p1);
			int PT_prev = PT0; // this is P_T[0]
			for (int t = 1; t <= max_t; ++t) {
				// PT[t] = PT[t-1] * (N - t + 1)/t * q/p1
				ll num = ( (N - (t - 1)) % MOD + MOD ) % MOD; // N - t + 1 mod
				int PT = PT_prev;
				PT = mulmod(PT, num);
				PT = mulmod(PT, invSmall[t]); // divide by t
				PT = mulmod(PT, q);
				PT = mulmod(PT, inv_p1);
				PT_prev = PT;

				// add contribution for this t
				Sbase = addmod(Sbase, mulmod(PT, H[t]));
			}
		}

		answer = mulmod(pow_n_kminus1, Sbase);
		cout << answer << "\n";
	}

	return 0;
}
