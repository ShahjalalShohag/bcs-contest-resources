#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int N = 5000 + 2;
string s;
int dp1[N][N], vis[N];
array<int, 3> dp2[N];
int is_pal(int l, int r) {
  if (l >= r) return 1;
  if (s[l] != s[r]) return 0;
  int &ret = dp1[l][r];
  if (~ret) return ret;
  return ret = is_pal(l + 1, r - 1);
}
array<int, 3> fn(int l, int r) {
  if (l > r) return {0, 0, 1};
  auto &ret = dp2[l];
  if (vis[l]) return ret;
  vis[l] = 1;
  ret = {0, 0, 0};
  if (is_pal(l, r)) ret = {1, 1, 1};
  for (int i = l, j = r; i < j; i++, j--) {
    if (is_pal(l, i) && is_pal(j, r)) {
      auto x = fn(i + 1, j - 1);
      ret[0] = (0ll + ret[0] + x[0] + 4ll * x[1] + 4ll * x[2]) % mod; 
      ret[1] = (0ll + ret[1] + x[1] + 2ll * x[2]) % mod;
      ret[2] = (ret[2] + x[2]) % mod;
    }
  }
  return ret;
}
void solve() {
  cin >> s;
  int n = s.size();
  for (int i = 0; i < n; i++) {
    vis[i] = 0;
    for (int j = 0; j < n; j++) {
      dp1[i][j] = -1;
    }
  }
  cout << fn(0, n - 1)[0] << '\n';
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) solve();
  return 0;
}