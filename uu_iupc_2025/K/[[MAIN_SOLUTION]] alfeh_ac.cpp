#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
#define ll long long int
int spf[N], prime_count[N];
std::vector<int> prime_list;
void prec() {
    for(int i = 2; i < N; i++) {
        if(!spf[i]) {
            prime_list.push_back(i);
            for(int j = i; j < N; j += i) {
                spf[j] = i;
                prime_count[j]++;
            }
        }
    }
}
std::vector<pair<int, int>> prim;
int arr[N];
void add_back_track(int i, int val, int cnt) {
  if(i >= prim.size()) {
    arr[val]+=cnt;
    return;
  }
  add_back_track(i + 1, val, cnt);
  for(int j = 0; j < prim[i].second; j++) {
    val *= prim[i].first; 
    add_back_track(i + 1, val, cnt);
  }  
}
int query_backtrack(int i, int val, int prime_carry) {
  if(i >= prim.size()) {
    if(!prime_carry) return 0;
    if(prime_carry&1) return arr[val];
    return -arr[val];
  }
  int ans = query_backtrack(i + 1, val, prime_carry);
  for(int j = 1; j <= prim[i].second / 2 + 1; j++) {
    val *= prim[i].first;
  }
  return ans + query_backtrack(i + 1, val, prime_carry + 1);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int t = 1; 
    cin >> t;
    while(t--) {
        int n; 
        cin >> n;
        std::vector<int> v(n);
        for(int &u:v) cin >> u;
        sort(v.rbegin(), v.rend());
        ll ans = 0;
        for(int i = 0; i < n; i++) {
          int j = i;
          while(j + 1 < n && v[j + 1] == v[i]) j++;
          int cnt = j - i + 1;
          if(v[i] == 1) {
            ans += 1LL * cnt * (cnt + 1) / 2;
            ans += 1LL * cnt * i;
            break;
          }
          prim.clear();
          int a = v[i];
          while(a > 1) {
            int b = spf[a];
            int x = 0;
            while(a % b == 0) {
              a /= b;
              x++;
            }
            prim.push_back({b, x});
          }

          int cur = i -  query_backtrack(0, 1, 0);
          add_back_track(0, 1, cnt);
          // int cur1 = 0;
          // for(int j1 = 0; j1 < i; j1++) {
          //   int lc = v[i] * v[j1] / __gcd(v[i], v[j1]);
          //   lc /= __gcd(v[i], v[j1]);
          //   cur1 += (lc % v[j1]) == 0;
          // }
          // // if(v[i] == 12)
          // // cout << cur << " " << i - all_ << "\n";

          ans += 1LL * cur * cnt;
          // cout << ans << ":n\"
          i = j;
        }

        for(int i = 1; i <= n * 10; i++) {
          arr[i] = 0;
        }
        

        cout << ans << "\n";
    
    }
    
    return 0;
}