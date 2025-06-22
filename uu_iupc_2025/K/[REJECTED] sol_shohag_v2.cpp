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
vector<int> d[N], md[N];
void solve() {
  int n; cin >> n;
  int a[n + 1];
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  vector<ll> mul(n * 10 + 1, 0);
  ll res = 0;
  for (int i = 1; i <= n; i++) {
    for (auto g: d[a[i]]) {
      int x = a[i] / g;
      if (__gcd(x, g) > 1) continue;
      int lim = (n * 10) / g / g;
      for (auto y: md[x]) {
        if (y <= lim) res += mob[y] * mul[g * g * y];
        else break;
      }
    }
    for (auto g: d[a[i]]) {
      mul[g]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    res += a[i] == 1;
  }
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
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      if (mob[i]) md[j].push_back(i);
    }
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}