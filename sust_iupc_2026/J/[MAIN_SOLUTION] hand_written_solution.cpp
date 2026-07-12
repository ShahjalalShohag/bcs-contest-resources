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

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;
        string a, b;
        cin >> a >> b;
        vector<ll> c(n + 1);
        for (int i = 1; i <= n; i++) cin >> c[i];

        string s = a + "#" + b;
        vector<int> z(s.size());
        z[0] = s.size();
        for (int i = 1, l = 0, r = 0; i < (int) s.size(); i++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }

        vector<int> border(s.size(), 0);
        for (int i = 1; i < (int) s.size(); i++) {
            if (z[i] == 0) continue;
            border[i + z[i] - 1] = max(border[i + z[i] - 1], z[i]);
        }
        for (int i = (int) s.size() - 1; i >= 1; i--) {
            border[i - 1] = max(border[i - 1], border[i] - 1);
        }

        vector<ll> cSum(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cSum[i] = cSum[border[i - 1]] + c[i];
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        vector<vector<int>> par(LOG, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; i++) par[0][i] = border[i - 1];
        for (int k = 1; k < LOG; k++)
            for (int i = 1; i <= n; i++)
                par[k][i] = par[k - 1][par[k - 1][i]];

        while (q--) {
            int l, r;
            cin >> l >> r;
            l += n, r += n;
            if (l == r || z[l] == 0 || border[r] == 0 || l + z[l] < r - border[r] + 1) {
                cout << 0 << "\n";
                continue;
            }
            int leaf = border[r];
            int R = min(r - l, leaf);
            int L = max(1, r - (l + z[l]) + 1);

            int curr = leaf;
            int bound = R;
            int y1, y2;
            if (curr <= bound) y1 =  curr;
            else {
                for (int k = LOG - 1; k >= 0; k--)
                    if (par[k][curr] > bound) curr = par[k][curr];
                y1 = par[0][curr];
            }

            curr = y1;
            bound = L - 1;
            if (curr <= bound) y2 = curr;
            else {
                for (int k = LOG - 1; k >= 0; k--)
                    if (par[k][curr] > bound) curr = par[k][curr];
                y2 = par[0][curr];
            }
            
            cout << cSum[y1] - cSum[y2] << "\n";
        }
    }

    return 0;
}