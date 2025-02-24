#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pii = pair<int, int>;
using pp = pair<pii, int>;

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
    bool operator()(const pp &x, const pp &y) const {
        auto a = x.first;
        auto b = y.first;
        return tie(a.first, b.second) < tie(b.first, a.second);
    }
};

struct RightComp {
    bool operator()(const pp &x, const pp &y) const {
        auto a = x.first;
        auto b = y.first;
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

        set<pp, LeftComp> lefts {
            {{-1, -1}, q},
            {{n+2, n+1}, q+1},
        };
        set<pp, RightComp> rights {
            {{-1, -1}, q},
            {{n+2, n+1}, q}
        };
        vector<ll> contribs(q+2);
        contribs[q] = 1;
        contribs[q+1] = 1;

        ll ans = modexpo(m, n);

        for(int i = 0; i<q; i++){
            pii cur;
            cin>>cur.first>>cur.second;
            
            auto lit = prev(lefts.upper_bound(make_pair(cur, i)));
            auto rit = prev(rights.upper_bound(make_pair(cur, i)));

            if (cur.second <= lit->first.second) {
                cout << ans << '\n';
                continue;
            }
            auto target_thing = *rit;
            auto target = target_thing.first;
            auto last_thing = *lit;
            auto last = last_thing.first;
            lit = next(lit);
            
            while(last != target) {

                last_thing = *lit;
                last = last_thing.first;
                auto next_lit = next(lit);

                ans = ans * modexpo(contribs[lit->second], MOD-2) % MOD;
                rights.erase(last_thing);
                lefts.erase(lit);

                lit = next_lit;
            }

            auto [lit2, _] = lefts.insert(make_pair(cur, i));
            auto [rit2, __] = rights.insert(make_pair(cur, i));

            lit = prev(lit2);
            rit = next(rit2);

            auto contrib = getContrib(lit->first, cur, m);
            ans = ans * contrib % MOD;
            contribs[i] = contrib;

            ans = ans * modexpo(contribs[rit->second], MOD-2) % MOD;
            contrib = getContrib(cur, rit->first, m);
            ans = ans * contrib % MOD;
            contribs[rit->second] = contrib;

            cout << ans << '\n';
        }
    }

    return 0;
}
