#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define all(x) x.begin(),x.end()
#define Max 10000000000000000

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

ll mod = 998244353;
ll n, a[300005];
pair<ll, ll> dp[1<<20];

pair<ll, ll> solve(ll mask){
    ll zero_count = 0;
    for(ll i = 0; i < n; i++) {
        if(!(mask & (1<<i))) zero_count++;
    }

    if(zero_count == 1) return {0, 1};
    if(dp[mask].first != -1) return dp[mask];

    pair<ll, ll> res = {0, 0};
    for(ll i = 0; i < n; i++) {
        if(!(mask & (1<<i))) {
            for(ll j = 0; j < i; j++) {
                if(!(mask & (1<<j))) {
                    ll scr = abs(a[i] - a[j]);
                    pair<ll, ll> temp2 = solve(mask | (1<<j));
                    pair<ll, ll> temp1 = solve(mask | (1<<i));

                    ll total_ways = (temp1.second + temp2.second) % mod;
                    ll total_score = (temp1.first + temp2.first + (total_ways * scr) % mod) % mod;

                    res.first = (res.first + total_score) % mod;
                    res.second = (res.second + total_ways) % mod;
                }
            }
        }
    }

    dp[mask] = res;
    return res;
}

ll bigmod(ll a, ll b)
{
    ll res = 1;
    a = a % mod;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}

int main()
{

    ll t;
    cin>>t;

    while(t--) {
        cin>>n;
        for(ll i = 0; i < n; i++) {
            cin>>a[i];
        }
        memset(dp, -1, sizeof(dp));
        pair<ll, ll> ans = solve(0);
        ll final_ans = (ans.first * bigmod(ans.second, mod - 2)) % mod;
        cout<<final_ans<<"\n";
    }

    return 0;
}