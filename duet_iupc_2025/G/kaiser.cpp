#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;

#define ll long long

ll fact[MAXN], inv_fact[MAXN];

ll bm(int a, int b) {
    if(!b) return 1;
    ll ret=bm(a,b/2);
    ret=(ret*ret)%MOD;
    if(b&1) ret=(ret*a)%MOD;
    return ret;
}

vector<int> sz;
vector<vector<int>> g;

ll dfs(int u) {
    ll curr = 1;
    ll tot = 1;
    for (auto v:g[u]) {
        ll w=dfs(v);
        curr=(curr*w)%MOD;
        curr=(curr*inv_fact[sz[v]])%MOD;
        tot+=sz[v];
    }
    curr=(curr*fact[tot-1])%MOD;
    sz[u]=tot;
    return curr;
}

int f(int n,vector<int>& par) {
    g.assign(n+1,{});
    sz.assign(n+1,0);
    for (int i=1;i<n;i++) g[par[i]].push_back(i);
    return dfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fact[0] = inv_fact[0] = 1;
    for (int i=1;i<MAXN;i++) fact[i]=(fact[i-1]*i)% MOD;
    inv_fact[MAXN-1]=bm(fact[MAXN-1],MOD-2);
    for(int i=MAXN-2;i>=0;i--) inv_fact[i]=(inv_fact[i+1]*(i+1))%MOD;

    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        vector<int>a(n),b(n);
        for (int i=0;i<n;i++) cin>>a[i];
        for (int i=0;i<n;i++) cin>>b[i];

        for (int i=0;i< n;i++) {
            if (a[i]!=-1) a[i]--;
            if (b[i]!=-1) b[i]--;
        }
        ll fa=f(n,a);
        ll fb=f(n,b);
        ll inv_fb=bm(fb,MOD-2);
        cout << (fa*inv_fb)%MOD<<'\n';
    }
}
