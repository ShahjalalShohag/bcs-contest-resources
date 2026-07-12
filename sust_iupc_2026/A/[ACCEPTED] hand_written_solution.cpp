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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t, mod = 998244353;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1), b(n + 1), pos(n + 1), cnt(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            cnt[b[i]]++;
        }

        set<int> s;
        vector<int> par(n + 1);
        par[n] = -1;

        for (int i = n; i >= 1; i--) {
            if (s.empty()) {
                s.insert(pos[i]);
                continue;
            }
            auto it = s.lower_bound(pos[i]);
            if (it != s.end()) {
                int idxR = *it;
                if (it != s.begin()) {
                    int idxL = *prev(it);
                    int node = min(a[idxL], a[idxR]);
                    par[i] = node;
                } else {
                    par[i] = a[idxR];
                }
            } else {
                int idx = *prev(it);
                par[i] = a[idx];
            }
            s.insert(pos[i]);
        }

        vector<int> subtreeSize(n + 1, 0), needCnt(n + 1, 0);
        for (int  i = 1; i < n; i++) {
            subtreeSize[i]++;
            subtreeSize[par[i]] += subtreeSize[i];

            needCnt[i] += cnt[i];
            needCnt[par[i]] += needCnt[i];
        }
        subtreeSize[n]++;
        needCnt[n] += cnt[n];

        ll ans = 1;
        for (int i = n; i >= 1 && ans; i--) {
            ll base = subtreeSize[i] - needCnt[i] + cnt[i];
            for (int k = 0; k < cnt[i]; k++) {
                ll f = base - k;
                if (f <= 0) { ans = 0; break; }
                ans = ans * f % mod;
            }
        }

        cout << ans << endl;
    }

    return 0;
}