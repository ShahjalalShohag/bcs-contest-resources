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

int dp[1000005], next_contributor[1000005];

int main()
{

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a.pb(x);
            dp[i] = 0;
            next_contributor[i] = -1;
        }

        stack<pair<int, int>> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && st.top().first <= a[i]) st.pop();
            if (!st.empty()) {
                next_contributor[i] = st.top().second;
            }
            st.push({a[i], i});
        }

        for (int j = 1; j <= k; j++) {
            int mx = 0;
            for (int i = n - 1; i >= 0; i--) {
                int tmp = mx + 1;
                if (next_contributor[i] != -1) {
                    tmp = max(tmp, dp[next_contributor[i]] + 1);
                }
                mx = max(mx, dp[i]);
                dp[i] = tmp;
            }
        }

        cout << dp[0] << endl;
    }

    return 0;
}