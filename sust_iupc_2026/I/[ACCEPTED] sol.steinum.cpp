#include <bits/stdc++.h>
using namespace std;

const int mx = 3e5 + 10, mod = 998244353, L = 3;
int T[mx * 60][L], z, n, k;
long long a[mx];

long long min(long long x) {
	long long ans = 0;
	int c = 0;
	for(int i = k - 1; i >= 0; i--) {
		int v = (x >> i) & 1;
		if(!T[c][v]) T[c][v] = ++z;
		if(T[T[c][v]][L - 1] == (1LL << i)) v ^= 1;
		if(!T[c][v]) T[c][v] = ++z;
		c = T[c][v]; ans ^= ((1LL << i) * v);
		T[c][L - 1]++;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t; cin >> t; while(t--) {
		int ans = 1; cin >> n >> k;
		for(int i = 0, b = ((1LL << k) - n) % mod; i < n; i++, b++) {
			cin >> a[i];
			ans = 1LL * ans * b % mod;
		}
		cout << ans << '\n';
		if(ans) {
			min(0);
			long long x = 0;
			for(int i = 0; i < n; i++) {
				x ^= a[i];
				long long b = min(x) ^ x; x ^= b;
				cout << b << " \n"[i + 1 == n];
			}
			for(int i = 0; i <= z + 3; i++) T[i][0] = T[i][1] = T[i][2] = 0;
			z = 0;
		}
	}
	return 0;
}