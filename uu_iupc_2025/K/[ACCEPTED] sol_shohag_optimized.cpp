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
vector<int> get_magic_vector(int n) {
    vector<int> v;
    while (n > 1) {
        int p = spf[n], e = 0;
        while (n % p == 0) e++, n /= p;
        int cur = 1;
        for (int i = 1; i <= e / 2 + 1; i++) {
            cur *= p;
        }
        v.push_back(cur);
    }
    return v;
}
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
  vector<int> mul(n * 10 + 1, 0);
  ll ans = 0;
  int tot = 0;
  for (int i = n * 10; i >= 2; i--) {
    if (!freq[i]) continue;
    auto v = get_magic_vector(i);
    int k = v.size();
    int res = 0;
    int prod[1 << k], sgn[1 << k];
    prod[0] = 1; sgn[0] = -1;
    for (int mask = 1; mask < (1 << k); mask++) {
        int lowbit = mask & -mask;
        prod[mask] = prod[mask ^ lowbit] * v[__builtin_ctz(lowbit)];
        sgn[mask] = -sgn[mask ^ lowbit];
        if (sgn[mask] == 1) res += mul[prod[mask]];
        else res -= mul[prod[mask]];
    }
    ans += 1LL * freq[i] * (tot - res);
    auto d_i = get_divs(i);
    for (auto g: d_i) {
      mul[g] += freq[i];
    }
    tot += freq[i];
  }
  ans += 1LL * freq[1] * tot;
  ans += 1LL * freq[1] * (freq[1] + 1) / 2;
  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  sieve();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}