#include<bits/stdc++.h>
using namespace std;

const int N = 1e7 + 9;
using ll = long long;


int spf[N];
vector<int> primes;
void sieve() {
  for(int i = 2; i < N; i++) {
    if (spf[i] == 0) spf[i] = i, primes.push_back(i);
    int sz = primes.size();
    for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++) {
      spf[i * primes[j]] = primes[j];
    }
  }
}

vector<pair<int, int>> factorize(int n) {
  vector<pair<int, int>> p;
  while (n > 1) {
    int k = spf[n];
    p.push_back({k, 1});
    n /= k;
    while (n % k == 0) {
      p.back().second++;
      n /= k;
    }
  }
  return p;
}

vector<int> get_divs(int n) { // not sorted
  vector<int> ans(1, 1);
  while (n > 1) {
    int k = spf[n];
    int cur = 1, sz = ans.size();
    while (n % k == 0) {
      cur *= k;
      n /= k;
      for (int i = 0; i < sz; i++) {
        ans.push_back(ans[i] * cur);
      }
    }
  }
  return ans;
}

int mob[N];
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}
vector<int> d[N];
void solve() {
  int n; cin >> n;
  int a[n + 1];
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> freq(n * 10 + 1, 0);
  for (int i = 1; i <= n; i++) {
    freq[a[i]]++;
  }
  vector<ll> mul(n * 10 + 1, 0);
  ll res = 0;
  for (int i = 1; i <= n * 10; i++) {
    if (!freq[i]) continue;
    auto d_i = get_divs(i);
    for (auto g: d_i) {
      int x = i / g;
      if (__gcd(x, g) > 1) continue;
      int lim = (n * 10) / g / g;
      auto d_x = get_divs(x);
      for (auto y: d_x) {
        if (y <= lim) res += 1LL * mob[y] * mul[g * g * y] * freq[i];
      }
    }
    for (auto g: d_i) {
      mul[g] += freq[i];
    }
  }
  res += 1LL * freq[1] * (freq[1] + 1) / 2;
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  sieve();
  mobius();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}