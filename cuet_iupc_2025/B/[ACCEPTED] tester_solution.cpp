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

int mod = 998244353;

int bigmod(int n, int p)
{
    int res = 1;
    while(p) {
        if(p % 2)
            res = ((ll) res * n) % mod;
        n = ((ll) n * n) % mod;
        p /= 2;
    }
    return res;
}

int main()
{

    int T;
    scanf("%d", &T);

    while(T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<int> a(n), freq(n + 1, 0), pref_freq(n + 1), prod(n + 1);
        pref_freq[0] = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            freq[a[i]]++;
        }

        for(int i = 1; i <= n; i++) {
            pref_freq[i] = pref_freq[i - 1] + freq[i];
            prod[i] = 0;
        }

        int m = min(k - 1, (int)log2(n));
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        dp[0][1] = 1;
        for(int i = 1; i <= m; i++) {
            for(int val = 2; val <= n; val++) {
                if(freq[val] == 0)
                    continue;
                for(int p = val; p <= n; p += val) {
                    int prev = p / val;
                    if(prev <= n && dp[i - 1][prev] != 0) {
                        dp[i][p] = ((ll) dp[i][p] + (ll) dp[i - 1][prev] * freq[val]) % mod;
                    }
                }
            }
        }

        prod[1] = bigmod(freq[1], k - 1);
        for(int i = 1; i <= m; i++) {
            int c = 1;
            for(int j = 1; j <= i; j++) {
                c = ((ll) c * (k - j)) % mod;
                c = ((ll) c * bigmod(j, mod - 2)) % mod;
            }
            int pow_freq1 = bigmod(freq[1], k - i - 1);
            for(int p = 2; p <= n; p++) {
                if(dp[i][p] == 0)
                    continue;
                int add = ((ll) dp[i][p] * c) % mod;
                add = ((ll) add * pow_freq1) % mod;
                prod[p] = ((ll) prod[p] + add) % mod;
            }
        }

        int ans = 0;
        for(int p = 1; p <= n; p++) {
            if(prod[p] == 0)
                continue;
            int fm = 0;
            int maxT = n / p;
            for(int t = 1; t <= maxT; t++) {
                int l = t * p;
                int r = min(n, (t + 1) * p - 1);
                int sumfreq = pref_freq[r] - pref_freq[l - 1];
                if(sumfreq) {
                    fm = ((ll) fm + (ll) t * sumfreq) % mod;
                }
            }
            prod[p] = ((ll) prod[p] * fm) % mod;
            ans = ((ll) ans + prod[p]) % mod;
        }

        printf("%d\n", ans);
    }

    return 0;
}