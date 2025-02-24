#include <bits/stdc++.h>
using namespace std;

#define ll long long int

ll mod = 998244353;
vector<ll> dp[5000];
ll base = 43, hashMod = 1000000403;
ll forwardHash[5000], backwardHash[5000], p[5000], invP[5000];
string s;

ll bigmod(ll n, ll x){
    if(!x) return 1;
    if(x % 2) return (n * bigmod(n, x - 1)) % hashMod;
    ll v = bigmod(n, x / 2);
    return (v * v) % hashMod;
}

ll getHashVal(ll l, ll r, bool isForwardHash){
    if(isForwardHash){
        ll hashVal = forwardHash[r];
        if(l){
            hashVal = (hashVal - forwardHash[l - 1] + hashMod) % hashMod;
            hashVal = (hashVal * invP[l]) % hashMod;
        }
        return hashVal;
    }
    else{
        ll hashVal = backwardHash[l];
        if(r < s.size() - 1){
            hashVal = (hashVal - backwardHash[r + 1] + hashMod) % hashMod;
            hashVal = (hashVal * invP[s.size() - (r + 1)]) % hashMod;
        }
        return hashVal;
    }
}

vector<ll> solve(ll l, ll r){
    if(l > r) return {0, 0, 0};
    if(!dp[l].empty()) return dp[l];

    dp[l] = {0, 0, 0};
    for(ll i = l, j = r; i < j; i++, j--){
        if(getHashVal(l, i, true) != getHashVal(l, i, false)) continue;
        if(getHashVal(j, r, true) != getHashVal(j, r, false)) continue;
        vector<ll> temp = solve(i + 1, j - 1);
        dp[l][0] = (dp[l][0] + temp[0] + 4 * temp[1] + 4 * temp[2]) % mod;
        dp[l][1] = (dp[l][1] + temp[1] + 2 * temp[2]) % mod;
        dp[l][2] = (dp[l][2] + temp[2]) % mod;
    }
    if(getHashVal(l, r, true) == getHashVal(l, r, false)){
        dp[l][0] = (dp[l][0] + 1) % mod;
        dp[l][1] = (dp[l][1] + 1) % mod;
        dp[l][2] = (dp[l][2] + 1) % mod;
    }

    if((r - l + 1) % 2 == 0){
        ll m = (l + r) / 2;
        if(getHashVal(l, m, true) == getHashVal(l, m, false)
            && getHashVal(m + 1, r, true) == getHashVal(m + 1, r, false)){
            dp[l][0] = (dp[l][0] + 4) % mod;
            dp[l][1] = (dp[l][1] + 2) % mod;
            dp[l][2] = (dp[l][2] + 1) % mod;
        }
    }

    return dp[l];
}

int main()
{   
    p[0] = 1;
    invP[0] = 1;
    for(int i = 1; i < 5000; i++){
        p[i] = (p[i-1] * base) % hashMod;
        invP[i] = bigmod(p[i], hashMod - 2);
    }


    ll t;
    cin>>t;

    while(t--){
        cin>>s;

        for(int i = 0, hashVal = 0; i < s.size(); i++){
            hashVal = (hashVal + p[i] * (s[i] - 'a' + 1)) % hashMod;
            forwardHash[i] = hashVal;
        }

        for(int i = s.size() - 1, hashVal = 0; i >= 0; i--){
            hashVal = (hashVal + p[s.size() - (i + 1)] * (s[i] - 'a' + 1)) % hashMod;
            backwardHash[i] = hashVal;
        }
        for(ll i = 0; i < s.size(); i++) dp[i].clear();
        vector<ll> ans = solve(0, s.size() - 1);
        cout<<ans[0]<<endl;
    }    

    return 0;
}