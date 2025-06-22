#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
const int mod = 1e9 + 7;
struct bol {
    int id;
    bol() {
        id = mod;
    }
};
struct segment_tree{
    std::vector<bol> t;
    int n;
    segment_tree(int _n) {
        t.resize(4 * _n + 1);
        n = _n;
    }
    bol merge(bol a,bol b) {
        bol c;
        c.id = min(a.id, b.id);
        return c;
    }
    int chk(int a,int b,int c,int d) {
        if(a > b || a > d || c > d || c > b)
            return 1;
        return 0;
    }
    bol query(int node, int l, int r, int le, int ri) {
        bol c;
        if(chk(l, r, le, ri))
            return c;
        if(l >= le && r <= ri)
            return t[node];
        int mi = (l + r) / 2;
        bol a = query(2 * node, l, mi, le, ri);
        bol b = query(2 * node + 1, mi + 1, r, le, ri);
        return merge(a, b);
    }
    bol query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    void update(int node, int l, int r, int ind, int val) {
        if(ind < l || ind > r)
            return;
        if(l == r) {
            t[node].id = min(t[node].id, val);
            return;
        }
        int mi = (l + r) / 2;
        update(2 * node, l, mi, ind, val);
        update(2 * node + 1, mi + 1, r, ind, val);
        t[node] = merge(t[2 * node], t[2 * node + 1]);
        return;
    }
    void update(int ind, int val) {
        update(1, 1, n, ind, val);
    }
};
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        long long int ans = 0;
        std::vector<int> v(n);
        std::vector<int> next_high(n + 1, n);
        for(int &u:v) cin >> u;
        segment_tree seg(n);
        for(int i = n - 1; i >= 0; i--) {
            next_high[i] = min(next_high[i], seg.query(v[i] + 1, n).id);
            seg.update(v[i], i);
        } 
        for(int i = 0; i < n; i++) {
            if(v[i] > 0) continue;
            int j = i; 
            int mx = 0;
            int zero_count = next_high[i] - i;
            ans += 1LL * zero_count * (zero_count + 1) / 2;
            ans -= 1LL * zero_count * zero_count;
            while(j < n) {
                int next_j = next_high[j];
                ans += 1LL * (v[j] + 1) * (next_j - j) * zero_count;
                if(v[next_j] > v[j] + 1) {
                    ans += 1LL * (v[j] + 1) * (n - next_j) * zero_count;
                    break;
                }
                j = next_j;
            }
            i += zero_count;
        }
        cout << ans << "\n";
    }
    return 0;
}
