#include<bits/stdc++.h>
using namespace std;

const int N = 1e7 + 9;
using ll = long long;

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
    for (auto g: d[i]) {
      int x = i / g;
      if (__gcd(x, g) > 1) continue;
      int lim = (n * 10) / g / g;
      for (auto y: d[x]) {
        if (y <= lim) res += 1LL * mob[y] * mul[g * g * y] * freq[i];
        else break;
      }
    }
    for (auto g: d[i]) {
      mul[g] += freq[i];
    }
  }
  res += 1LL * freq[1] * (freq[1] + 1) / 2;
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      d[j].push_back(i);
    }
  }
  mobius();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}