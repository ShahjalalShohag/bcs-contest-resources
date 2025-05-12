#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 300005

int n, a[mxn], ans;
vector<int>g[mxn];

int dfs(int node, int par){
    int now = a[node];

    for(int b : g[node]){
        if(b-par){
            int nxt = dfs(b,node);
            if(nxt) ans++;
            now = max(now,nxt);
        }
    }

    return now;
}

int main()
{
    fastio;

    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n+2; i++){
            g[i].clear();
        }

        int tot=0, root=-1;

        for(int i=1; i<=n; i++){
            cin>>a[i], tot+=a[i];
            if(a[i]) root=i;
        }

        for(int i=0; i<n-1; i++){
            int u, v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        if(tot%2){
            cout<<-1<<'\n';
            continue;
        }

        if(tot==0){
            cout<<0<<'\n';
            continue;
        }

        ans = 0;

        dfs(root,-1);

        cout<<ans<<'\n';

    }
    
    return 0;
}