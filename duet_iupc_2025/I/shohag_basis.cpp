#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
using ll = long long;

template<typename T = int, int B = 31>
struct Basis {
  T a[B];
  Basis() {
    memset(a, 0, sizeof a);
  }
  void insert(T x){
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (a[i]) x ^= a[i];
        else {
          a[i] = x;
          break;
        }
      }
    }
  }
};


void solve() {
  int n; cin >> n;
  vector<int> a(n);
  Basis<int, 22> B;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    B.insert(a[i]);
  }
  int cnt = 0;
  for (int i = 0; i < 22; i++) cnt += B.a[i] > 0;
  if (cnt < n and n >= 22) {
    cout << 0 << '\n';
    return;
  }
  ll ans = 1e18;
  for (int mask = 1; mask < (1 << n) - 1; mask++) {
    int x = 0, o = 0;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        x ^= a[i];
      } else {
        o |= a[i];
      }
    }
    ans = min(ans, 1LL * x * o);
  }
  cout << ans << '\n';

}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}