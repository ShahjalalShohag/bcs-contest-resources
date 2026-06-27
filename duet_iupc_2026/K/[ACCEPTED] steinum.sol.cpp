#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned ll
#define lll __int128
#define ulll unsigned lll

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ull pow(ull a, ull t, ull mod) { ull r = 1; for (; t; t >>= 1, a = (ulll)a * a % mod)if (t & 1)r = (ulll)r * a % mod; return r; }
bool isprime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	          s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A) {
		ull p = pow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)p = (ulll)p * p % n;
		if (p != n - 1 && i != s) return 0;
	} return 1;
}

ll brent(ll n) {
	if (n % 2 == 0) return 2;
	ll y = rng() % (n - 1) + 1;
	ll c = rng() % (n - 1) + 1;
	ll m = rng() % (n - 1) + 1;
	ll g = 1, r = 1, q = 1, ys, x;
	while (g == 1) {
		x = y;
		for (int i = 0; i < r; i++) y = ((ulll)y * y + c) % n;
		ll k = 0;
		while ( k < r && g == 1 ) {
			ys = y;
			for (int i = 0; i < min(m, r - k); i++) {
				y = ((ulll)y * y + c) % n;
				q = ((ulll)q * abs(x - y)) % n;
			} g = __gcd(q, n); k = k + m;
		} r *= 2;
	}
	if (g == n) {
		while (true) {
			ys = ((ulll)ys * ys + c) % n;
			g = __gcd(abs(x - ys), n);
			if (g > 1) break;
		}
	} return g;
}

struct Lagrange {
	int n, mod;
	vector<int> y, c;
	Lagrange(vector<int> _y,int _mod):n(_y.size()-1),mod(_mod),y(_y){
		vector<int> f(n+1),g(n+1); f[0]=1;
		for(int i=1;i<=n;i++) f[i]=1LL*f[i-1]*i%mod;
		g[n]=pow(f[n],mod-2,mod);
		for(int i=n;i;i--) g[i-1]=1LL*g[i]*i%mod;
		c.resize(n+1);
		for(int i=0;i<=n;i++) c[i]=((n-i)&1?mod-1:1)*1LL*g[i]%mod*g[n-i]%mod;
	}

	int operator()(long long x){
		x%=mod; if(x<=n) return y[x];
		vector<int> L(n+2,1),R(n+2,1);
		for(int i=0;i<=n;i++) L[i+1]=1LL*L[i]*(x-i+mod)%mod;
		for(int i=n;i>=0;i--) R[i]=1LL*R[i+1]*(x-i+mod)%mod;
		long long ans=0;
		for(int i=0;i<=n;i++) ans=(ans+1LL*y[i]*c[i]%mod*L[i]%mod*R[i+1])%mod;
		return ans;
	}
};

set<ll> factor(ll n){
    if(n == 1) return {};
    if(isprime(n)) return {n};
    ll d = brent(n);
    auto a = factor(d), b = factor(n/d);
    a.merge(b);
    return a;
}

const int mod = 998244353;

int F(ll n) {
	if(n <= 2) return 1;
	auto P = factor(n);
	ll s = 0, r = 0;
	vector<int> y((int)P.size() + 2);
	for(int i = 0; i <= (int)P.size() + 1; i++) {
		ll prod = 1;
		for(ll p: P) prod *= (p - i);
		s = (s + prod) % mod;
		if(i == 0) r = prod;
		y[i] = s;
	}
	Lagrange f(y, mod);
	ll ans = (f((*P.begin()) - 1) - f(0)) % mod;
	if(ans < 0) ans += mod;
	return (ans * ((n / r) % mod)) % mod;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while(t--) {
		long long n; cin >> n;
		cout << F(n) << '\n';
	}
}