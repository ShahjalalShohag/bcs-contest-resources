#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
using ll = long long;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  if (n > 4) {
    cout << "NO\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      string p = s.substr(i, j - i + 1);
      if (stoi(p) % (j - i + 1) != 0) {
        cout << "NO\n";
        return;
      }
    }
  }
  cout << "YES\n";
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