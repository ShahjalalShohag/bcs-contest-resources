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
  vector<int> freq(n * 10 + 1, 0);
  for (int i = 1; i <= n; i++) {
    freq[a[i]]++;
  }
  vector<pair<int, int>> v[n * 10 + 1];
  for (int i = 1; i <= n; i++) {
    if (!freq[i]) continue;
    for (auto g: d[i]) {
      v[g].push_back({i / g, freq[i]});
    }
  }
  ll res = 0;
  vector<int> mul(n * 10 + 1, 0);
  for (int g = 1; g <= n * 10; g++) {
    sort(v[g].begin(), v[g].end(), greater<pair<int, int>>());
    for (int i = 0; i < (int)v[g].size(); i++) {
      int x = v[g][i].first;
      int cnt = v[g][i].second;
      if (x % g == 0) {
        for (auto y: md[x]) {
          res += 1LL * mob[y] * mul[y] * cnt;
        }
      }
      for (auto y: md[x]) {
        mul[y] += cnt;
      }
    }
    for (int i = 0; i < (int)v[g].size(); i++) {
      int x = v[g][i].first;
      for (auto y: md[x]) {
        mul[y] = 0;
      }
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