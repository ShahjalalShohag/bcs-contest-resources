
// 12 ==> 479001600 ==> 527656359
// 11 ==> 39916800 ==> 644056242
// 10 ==> 3628800 ==> 821984089

#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353
#define MAX 500006

typedef long long ll;

ll bit[MAX], a[MAX], fact[MAX];
bool is_inf[MAX]; 
int n;

void precal(){
    fact[0] = 1;
    for(int i = 1; i < MAX; i++) {
        fact[i] = (fact[i-1]*i) % MOD;
    }
}

void add(int i, ll val){
    val %= MOD;
    if (val < 0) val += MOD;
    while(i <= n) {
        bit[i] = (bit[i] + val) % MOD;
        i += i&(-i);
    }
}

ll query(int i){
    ll sum = 0;
    while(i > 0) {
        sum = (sum + bit[i]) % MOD;
        i -= i&(-i);
    }
    return sum;
}

void solve() {
    int q; cin >> n >> q;

    for(int i = 0; i <= n; i++) bit[i] = 0;
    set<int> active;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        is_inf[i] = 0;
        add(i, a[i]);

        if(a[i] == 0 || a[i] > 2)
            active.insert(i);
    }

    while(q--) {
        int t, l, r;
        cin >> t >> l >> r;

        if (t == 1) {
            auto it = active.lower_bound(l);
            while (it != active.end() && *it <= r) {
                int i = *it;
                ll old_val = a[i], new_val;
                bool next_inf = 0;

                if (is_inf[i]) {
                    new_val = 0;
                    next_inf = 1; 
                } 
                else if (old_val == 3628800) {          
                    new_val = 821984089;
                    next_inf = 1; 
                } 
                else if (old_val == 39916800) {    
                    new_val = 644056242;
                    next_inf = 1; 
                } 
                else if (old_val == 479001600) {   
                    new_val = 527656359;
                    next_inf = 1;
                } 
                else if (old_val >= MAX) {
                    new_val = 0;
                    next_inf = 1;
                } 
                else {
                    new_val = fact[old_val];
                    if (old_val == 10 || old_val == 11 || old_val == 12) next_inf = 0; 
                    else if (old_val >= 13) next_inf = 1;
                    else next_inf = 0;
                }

                add(i, new_val - old_val);
                a[i] = new_val;
                is_inf[i] = next_inf;

                bool stable = (is_inf[i] && a[i] == 0) || (!is_inf[i] && (a[i] == 1 || a[i] == 2));
                
                if (stable) it = active.erase(it);
                else it++;
            }
        } else {
            ll ans = query(r) - query(l - 1);
            if (ans < 0) ans += MOD;
            cout << ans << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin >> TC;

    precal();

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}