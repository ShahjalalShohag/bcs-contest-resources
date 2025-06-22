#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while(T--){
        int n; 
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) 
            cin >> a[i];

        // 1) Compute next_greater[i]: first index > a[i] to the right, or n
        vector<int> nxt(n,n);
        stack<int> st;
        for(int i = 0; i < n; i++){
            while(!st.empty() && a[i] > a[st.top()]){
                nxt[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        // 2) dp[i] = number of record‐maxima in subarray a[i..] 
        //    assuming each step jumps to its next greater
        vector<ll> dp(n+1, 0);
        ll ans = 0;
        for(int i = n - 1; i >= 0; i--){
            dp[i] = 1 + (nxt[i] < n ? dp[nxt[i]] : 0);
            ans += dp[i];
        }

        cout << ans << "\n";
    }
    return 0;
}
