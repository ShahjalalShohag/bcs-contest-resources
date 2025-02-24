#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353L;

int main() {
    int T;
    cin>>T;
    while(T--) {
        string s;
        cin>>s;
        int n = s.size();
        vector<vector<bool>> is_palin(n, vector<bool>(n,false));
        for(int i=0;i<n;i++) is_palin[i][i] = true;
        for(int i=0;i+1<n;i++) is_palin[i][i+1] = s[i] == s[i+1];
        for(int len=3;len<=n;len++)
        {
            for(int i=0;i+len-1<n;i++)
            {
                int j = i+len-1;
                is_palin[i][j] = is_palin[i+1][j-1] and s[i] == s[j];
            }
        }
        vector<vector<ll>> save(n);
        auto dp = [&](auto &&dp, int l,int r) -> vector<ll> /* 3 sized vector */ {
            if(l == r+1)
            {
                // empty string, k=0
                return {1L, 0LL, 0LL};
            }
            vector<ll> &ans = save[l];
            if(!ans.empty()) return ans;
            ans = {0,0,0};
            if(is_palin[l][r])
            {
                ans[0] = 1;
                ans[1] = 1;
                ans[2] = 1;
            }
            for(int len = 1; len *2 <= r-l+1; len++)
            {
                int ii = l+len-1;
                int jj = r-len+1;
                if(is_palin[l][ii] and is_palin[jj][r])
                {
                    auto x = dp(dp, ii+1, jj-1);
                    ans[0] = (ans[0] + x[0]) % mod;
                    ans[1] = (ans[1] + x[1] + 2 * x[0]) % mod;
                    ans[2] = (ans[2] + x[2] + 4 * x[1] + 4* x[0])% mod;
                }
            }
            return ans;
        };
        ll ans = dp(dp,0, n-1)[2];
        cout<<ans<<"\n";
    }
}