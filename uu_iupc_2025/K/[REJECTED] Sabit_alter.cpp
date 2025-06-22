#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt")

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using ld = long double;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree < T, null_type, less<T>,
rb_tree_tag,
tree_order_statistics_node_update >;

#ifdef SA_DEBUG
template <class T>
void print(T a) {cerr << a << endl;}
template <class T, class... V> 
void print(T a, V... b) {cerr << a << ", "; print(b...);}
#define dbg(...) cerr << "[" << __LINE__ << "] " << #__VA_ARGS__ << " :: ", print(__VA_ARGS__)
#else
#define dbg(...) 7
#endif

#define eb emplace_back
#define fi first
#define se second

const ll INFL = 2e18;
const int INF = 1e9;
const double PI = acos(-1);
const ll mod = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.fi << ' ' << a.se; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.fi >> a.se; return s;
}

template<class T> 
ostream& operator << (ostream &s, vector<T> a){
	for(int i = 0; i < (int)a.size(); i++){
		if(i > 0)s << ' ' ; 
		s << a[i];
	} return s;
}

template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}

template<class T> 
void input(T a[], int l, int r, istream &s = cin){
	while(l <= r)s >> a[l++];
}

template<class T> 
void output(T a[], int l, int r, bool en = true, ostream &s = cout){
	while(l <= r){ s << a[l++];
		if(l <= r) s << ' ';
	} if(en)s << "\n";
}



const int N = 1e6+3, K = 26;
//====================================================================//

int primes[N];
int bs[N];
int pind = 0;
vector<ll> dv[N];
void sieve(){
	pind = 0;
	for(int i = 0; i < N; ++i)bs[i] = 0, dv[i].clear();
	bs[1] = 1;
	for(int i = 1; i < N; ++i){
		if(bs[i] == 0){
			primes[pind++] = i;
			
		}
		for(int j = i; j < N; j += i){
			if(i > 1)bs[j] = 1;
			dv[j].push_back(i);
		}
	}
}

int mu[N];
int cnt[N];
void mobius(){
    memset(mu, -1, sizeof mu);
    mu[1] = 1;
    for(int i = 2; i < N; i++)
        for(int j = (i << 1) ; j < N; j += i)mu[j] -= mu[i];
}

void testcase(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(auto &x : v)cin >> x;
	sort(v.begin(), v.end());
	ll ans = 0;
	for(auto x : v){
		for(int y : dv[x])cnt[y]++;
		vector<ii> p;
		int temp = x;
		for(int i = 0; primes[i] * primes[i] <= temp; i++){
			if(temp % primes[i] == 0){
				int a = 0;
				while(temp % primes[i] == 0){
					a++;
					temp /= primes[i];
				}
				p.eb(primes[i], a);
			}
		}
		if(temp > 1)p.eb(temp, 1);
		temp = p.size();
		for(int i = 0; i < (1 << temp); i++){
			int g = 1;
			for(int j = 0; j < temp; j++){
				if(i >> j & 1){
					for(int k = 0; k < p[j].se; k++)g *= p[j].fi;
				}
			}
			if(g > N / g)continue;
			int G = g * g;
			int g2 = x / g;
			for(auto y : dv[g2]){
				if(y < N / G)
					ans += mu[y] * cnt[G * y];
				else 
					break;
			}
		}
		
		 
	}
	for(auto x : v){
		for(int y : dv[x])cnt[y]--;
	}
	cout << ans << "\n";
	return;
}





int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	sieve();mobius();
	int T = 1;
	cin >> T;
	double mx = 0;
	for(int qq = 1; qq <= T; ++qq){
		//cout << "Case #" << qq << ": ";
		clock_t start = clock();
		testcase();
		mx = max(mx, (double)(clock() - start) / CLOCKS_PER_SEC);
	}
	//cout << mx << endl;
	return 0;
}
