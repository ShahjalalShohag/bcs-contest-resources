#include<bits/stdc++.h>
using namespace std;

const int N = 1e7 + 9;
using ll = long long;

vector<int> d[N];
void solve() {
  int n; cin >> n;
  int a[n + 1];
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  vector<ll> mul(n * 10 + 1, 0), ans(n * 10 + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (auto g: d[a[i]]) {
      if (1LL * g * g <= n) {
        ans[g] += mul[g * g];
      }
    }
    for (auto g: d[a[i]]) {
      mul[g]++;
    }
  }
  for (int i = n * 10; i >= 1; i--) {
    for (int j = i + i; j <= n * 10; j += i) {
      ans[i] -= ans[j];
    }
  }
  ll res = 0;
  for (int i = 1; i <= n * 10; i++) {
    res += ans[i];
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
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}