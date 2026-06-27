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

int main()
{

    ll t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a;
        for (ll i = 0; i < n; i++){
            ll x;
            cin >> x;
            if(x == 1 && a.empty()) continue;
            a.pb(x);
        }

        if(a.size() == 0) {
            cout << 0 << endl;
            continue;
        }

        n = a.size();
        while (a[n - 1] == 1) {
            a.pop_back();
            n--;
        }
        sort(all(a));
        if(a[0] == a[n - 1]) {
            cout << 1 << endl;
            continue;
        }
        cout << 2 << endl;
    }

    return 0;
}