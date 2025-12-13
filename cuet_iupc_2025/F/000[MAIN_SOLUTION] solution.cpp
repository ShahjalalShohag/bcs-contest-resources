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

    ll T;
    scanf("%lld", &T);

    while (T--) {
        ll n;
        scanf("%lld", &n);
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }

        sort(all(a));
        
        ll ans = 0;
        for(ll i = 0, sum = 0; i < n; i++) {
            sum = (sum + a[i]) % mod;
            ll curr = (a[i] * (i + 1)) % mod;
            ll scr = (curr - sum + mod) % mod;
            ans = (ans + scr) % mod;
        }

        ans = (ans * 2) % mod;
        ans = (ans * bigmod(n, mod - 2)) % mod;
        printf("%lld\n", ans);
    }
    

    return 0;
}