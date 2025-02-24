#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pii = pair<int, int>;

const int MAX = 1e6+5;
const ll MOD = 998244353;

ll modexpo(ll x, ll n) {
    ll res = 1;
    while(n) {
        if (n&1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}

ll fact[MAX], factinv[MAX];

void precal() {
    fact[0] = 1;
    for(int i = 1; i < MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    factinv[MAX-1] = modexpo(fact[MAX-1], MOD-2);
    for(int i = MAX-1; i>=1; i--) {
        factinv[i-1] = factinv[i] * i % MOD;
    }
}

ll npr(int n, int r) {
    return fact[n] * factinv[n-r] % MOD;
}

struct LeftComp {
    bool operator()(const pii &a, const pii &b) const {
        return tie(a.first, b.second) < tie(b.first, a.second);
    }
};

struct RightComp {
    bool operator()(const pii &a, const pii &b) const {
        return tie(a.second, b.first) < tie(b.second, a.first);
    }
};

int common(const pii &a, const pii &b) {
    if (a.second < b.first) return 0;
    return a.second + 1 - b.first;
}

ll getContrib(const pii &a, const pii &b, int m) {
    auto com = common(a, b);
    auto noncom = b.second+1 - b.first - com;
    return npr(m - com, noncom) * modexpo(m, noncom * (MOD-2)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precal();

    int tc;
    cin>>tc;

    for(int cs = 1; cs <= tc; cs++){
        int n, m, q;
        cin>>n>>m>>q;

        set<pii, LeftComp> lefts {
            {-1, -1},
            {n+2, n+1},
        };
        set<pii, RightComp> rights {
            {-1, -1},
            {n+2, n+1},
        };
        map<pii, ll> contribs{
            {{-1, -1}, 1},
            {{n+2, n+1}, 1},
        };

        ll ans = modexpo(m, n);

        for(int i = 0; i<q; i++){
            pii cur;
            cin>>cur.first>>cur.second;
            
            auto lit = prev(lefts.upper_bound(cur));
            auto rit = prev(rights.upper_bound(cur));

            if (cur.second <= lit->second) {
                cout << ans << '\n';
                continue;
            }
            auto target = *rit;
            auto last = *lit;
            lit = next(lit);
            
            while(last != target) {

                last = *lit;
                auto next_lit = next(lit);

                ans = ans * modexpo(contribs[*lit], MOD-2) % MOD;
                contribs.erase(*lit);
                rights.erase(*lit);
                lefts.erase(lit);

                lit = next_lit;
            }

            auto [lit2, _] = lefts.insert(cur);
            auto [rit2, __] = rights.insert(cur);

            lit = prev(lit2);
            rit = next(rit2);

            auto contrib = getContrib(*lit, cur, m);
            ans = ans * contrib % MOD;
            contribs[cur] = contrib;

            ans = ans * modexpo(contribs[*rit], MOD-2) % MOD;
            contrib = getContrib(cur, *rit, m);
            ans = ans * contrib % MOD;
            contribs[*rit] = contrib;

            cout << ans << '\n';
        }
    }

    return 0;
}
