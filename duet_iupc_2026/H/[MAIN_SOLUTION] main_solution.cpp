#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
  vector<int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    if (c + 1 < val_range) ++l[c + 1];
    ++r[c];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i)
    SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA)
    if (i >= 1 && sl[i - 1]) {
      SA[l[vec[i - 1]]++] = i - 1;
    }
  fill(r.begin(), r.end(), 0);
  for (int c : vec)
    ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
    if (i >= 1 && !sl[i - 1]) {
      SA[--r[vec[i - 1]]] = i - 1;
    }
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
  const int n = vec.size();
  vector<int> SA(n), lms_idx;
  vector<bool> sl(n);
  sl[n - 1] = false;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  induced_sort(vec, val_range, SA, sl, lms_idx);
  vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i)
    if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
      new_lms_idx[k++] = SA[i];
    }
  int cur = 0;
  SA[n - 1] = cur;
  for (size_t k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] != vec[j]) {
      SA[j] = ++cur;
      continue;
    }
    bool flag = false;
    for (int a = i + 1, b = j + 1;; ++a, ++b) {
      if (vec[a] != vec[b]) {
        flag = true;
        break;
      }
      if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
        flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
        break;
      }
    }
    SA[j] = (flag ? ++cur : cur);
  }
  for (size_t i = 0; i < lms_idx.size(); ++i)
    lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < (int)lms_idx.size()) {
    auto lms_SA = SA_IS(lms_vec, cur + 1);
    for (size_t i = 0; i < lms_idx.size(); ++i) {
      new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
  }
  induced_sort(vec, val_range, SA, sl, new_lms_idx);
  return SA;
}
vector<int> suffix_array(const string &s, const int LIM = 128) {
  vector<int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec));
  vec.back() = '!';
  auto ret = SA_IS(vec, LIM);
  ret.erase(ret.begin());
  return ret;
}
struct SuffixArray {
  int n;
  string s;
  vector<int> sa, rank, lcp;
  static const int LG = 19;
  vector<vector<int>> t;
  vector<int> lg;
  SuffixArray() {}
  SuffixArray(string _s) {
    n = _s.size();
    s = _s;
    sa = suffix_array(s);
    rank.resize(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    costruct_lcp();
    prec();
    build();
  }
  void costruct_lcp() {
    int k = 0;
    lcp.resize(n - 1, 0);
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = sa[rank[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k])  k++;
      lcp[rank[i]] = k;
      if (k)  k--;
    }
  }
  void prec() {
    lg.resize(n, 0);
    for (int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
  }
  void build() {
    int sz = n - 1;
    t.resize(sz);
    for (int i = 0; i < sz; i++) {
      t[i].resize(LG);
      t[i][0] = lcp[i];
    }
    for (int k = 1; k < LG; ++k) {
      for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
        t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
      }
    }
  }
  int query(int l, int r) { // minimum of lcp[l], ..., lcp[r]
    int k = lg[r - l + 1];
    return min(t[l][k], t[r - (1 << k) + 1][k]);
  }
  int get_lcp(int i, int j) { // lcp of suffix starting from i and j
    if (i == j) return n - i;
    int l = rank[i], r = rank[j];
    if (l > r) swap(l, r);
    return query(l, r - 1);
  }
};
 
// sum over all suffix pairs (a < b) of lcp(a, b), via a monotonic stack on the LCP array
ll get_lcp_pair_sum(SuffixArray& F) {
    int n = F.n;
    vector<int> h = F.lcp; 
    h.insert(h.begin(), 0); // h[k] = lcp(sa[k-1], sa[k])
    vector<ll> left(n, 0), right(n, 0);
    stack<int> st;
    for (int k = 1; k < n; k++) {
        while (!st.empty() && h[st.top()] > h[k]) st.pop();
        int prev = st.empty() ? 0 : st.top();
        left[k] = k - prev;
        st.push(k);
    }
    while (!st.empty()) st.pop();
    for (int k = n - 1; k >= 1; k--) {
        while (!st.empty() && h[st.top()] >= h[k]) st.pop();
        int nxt = st.empty() ? n : st.top();
        right[k] = nxt - k;
        st.push(k);
    }
    ll tot = 0;
    for (int k = 1; k < n; k++) tot += (ll)h[k] * left[k] * right[k];
    return tot;
}
 
// all maximal runs (l, r, primitive period p), via forward/backward SuffixArray
vector<array<int, 3>> get_runs(SuffixArray& Fwd, SuffixArray& Bwd, int n) {
    auto LF = [&](int i, int j) { return Fwd.get_lcp(i, j); };
    auto LB = [&](int i, int j) { if (i < 0 || j < 0) return 0; return Bwd.get_lcp(n - 1 - i, n - 1 - j); };
    map<pair<int, int>, int> best;
    for (int p = 1; 2 * p <= n; p++)
        for (int i = 0; i + p < n; i += p) {
            int j = i + p, fw = LF(i, j), bw = LB(i - 1, j - 1); // extend the period-p tandem both ways
            if (fw + bw >= p) {
                int l = i - bw, r = j + fw - 1; // maximal interval with period p
                if (r - l + 1 >= 2 * p) {
                    auto key = make_pair(l, r);
                    if (!best.count(key) || p < best[key]) best[key] = p; // keep primitive period
                }
            }
        }
    vector<array<int, 3>> res;
    for (auto& kv : best) res.push_back({kv.first.first, kv.first.second, kv.second});
    return res;
}
 
// R[x] = number of squares whose left half starts exactly at x
vector<ll> compute_R(const vector<array<int, 3>>& runs, int n) {
    vector<ll> R(n, 0);
    for (auto& a : runs) {
        int l = a[0], r = a[1], p = a[2], hi = r - 2 * p + 1;
        for (int x = l; x <= hi; x++) R[x] += (((ll)(r - x + 1) / 2) / p);
    }
    return R;
}

void solve() {
    string s; cin >> s;
    int n = s.size();
    if (n <= 1) { 
        cout << 0 << '\n'; 
        return; 
    }
    string srev = s;
    reverse(srev.begin(), srev.end());
    SuffixArray F(s), Bk(srev);

    ll sum_lcp = get_lcp_pair_sum(F);
    auto runs_F = get_runs(F, Bk, n); // runs of s

    ll overlap = 0;
    for (auto& a : runs_F) {
        int l = a[0], r = a[1], p = a[2], Lp = r - l + 1;
        for (int d = p; d < Lp; d += p) { // offset d = multiple of the primitive period
            int aHi = min(r - d, r + 1 - 2 * d);
            if (aHi < l) continue;
            ll C = r + 1 - 2 * d, cnt = aHi - l + 1;
            ll suma = ((ll)(l + aHi) * cnt) / 2;
            overlap += (ll)C * cnt - suma; // sum of (C - a) over a = l..aHi
        }
    }
    ll A = sum_lcp - overlap;

    vector<ll> R = compute_R(runs_F, n);   // squares starting at c
    auto runs_R = get_runs(Bk, F, n);      // runs of the reversed string
    vector<ll> Rr = compute_R(runs_R, n);  // squares starting at position in reversed string
    ll B = 0;
    for (int c = 1; c <= n - 1; c++) B += Rr[n - c] * R[c]; // L(c) = Rr[n-c] = squares ending at c-1 in s

    cout << 2 * A + B << '\n';
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
