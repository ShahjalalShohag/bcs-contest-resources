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

int par[600005], comp_size[600005], comp_type[600005];

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

int bigmod(int a, int p, int m) {
    int res = 1;
    a = a % m;
    while (p > 0) {
        if (p & 1) res = ((ll) res * (ll) a) % m;
        p = p >> 1;
        a = ((ll) a * (ll) a) % m;
    }
    return res;
}

int main()
{

    int t, mod = 998244353;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<pair<int, int>> guests(n);
        vector<int> colors;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &guests[i].first, &guests[i].second);
            colors.pb(guests[i].first);
            colors.pb(guests[i].second);
        }

        sort(all(colors));
        colors.erase(unique(all(colors)), colors.end());

        for (int i = 0; i < (int)colors.size(); i++) {
            par[i] = i;
            comp_size[i] = 1;
            comp_type[i] = 0;
        }

        ll ans = 1;

        for (int i = 0; i < n; i++) {
            if(ans == 0) {
                printf("0");
                if(i < n - 1) printf(" ");
                else printf("\n");
                continue;
            }
            guests[i].first = lower_bound(all(colors), guests[i].first) - colors.begin();
            guests[i].second = lower_bound(all(colors), guests[i].second) - colors.begin();

            int u = find(guests[i].first);
            int v = find(guests[i].second);
            if (u != v) {
                par[u] = v;
                if (comp_type[v] == 0) ans = (ans * bigmod(comp_size[v], mod - 2, mod)) % mod;
                else ans = (ans * bigmod(2, mod - 2, mod)) % mod;
                if (comp_type[u] == 0) ans = (ans * bigmod(comp_size[u], mod - 2, mod)) % mod;
                else ans = (ans * bigmod(2, mod - 2, mod)) % mod;
                comp_size[v] += comp_size[u];

                if (comp_type[u] == 1 && comp_type[v] == 1) {
                    ans = 0;
                }
                else if (comp_type[u] == 1 || comp_type[v] == 1) {
                    ans = (ans * 2) % mod;
                    comp_type[v] = 1;
                }
                else {
                    ans = (ans * comp_size[v]) % mod;
                }
            }
            else {
                if (comp_type[v] == 0) {
                    ans = (ans * bigmod(comp_size[v], mod - 2, mod)) % mod;
                    ans = (ans * 2) % mod;
                    comp_type[v] = 1;
                }
                else {
                    ans = 0;
                }
            }

            printf("%d", (int) ans);
            if(i < n - 1) printf(" ");
            else printf("\n");
        }
    }

    return 0;
}