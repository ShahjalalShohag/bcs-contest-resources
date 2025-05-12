#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 300005

int n, a[mxn], ans, flag, sub[mxn];
vector<int>g[mxn];

void dfs0(int node, int par){
    sub[node]=a[node];

    for(int b : g[node]){
        if(b-par){
            dfs0(b,node);
            sub[node]+=sub[b];
        }
    }
}

void dfs(int node, int par){
    int leaf=1, ch=-1;

    for(int b : g[node]){
        if(b-par){
            leaf=0;
            if(sub[b]) ch=b;
        }
    }

    if(leaf){
        if(a[node]){
            flag=0;
        }
        return;
    }

    if(a[node]){
        if(ch==-1){
            flag=0;
            return;
        }
        ans++;
        a[node]=0;
        if(a[ch]) sub[ch]--;
        else sub[ch]++;
        a[ch]^=1;
    }

    for(int b : g[node]){
        if(b-par){
            dfs(b,node);
        }
    }
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
            sub[i]=0;
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
        flag=1;

        dfs0(root,-1);
        dfs(root,-1);

        if(flag) cout<<ans<<'\n';
        else cout<<-1<<'\n';

    }
    
    return 0;
}