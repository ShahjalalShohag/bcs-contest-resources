#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 300005

int n, a[mxn], p[mxn], vis[mxn];
vector<int>g[mxn], v;

void bfs(){
    v.clear();

    queue<int>q;
    vis[1]=1;
    q.push(1);

    while(!q.empty()){
        int node = q.front();
        q.pop();
        v.push_back(node);

        for(int a : g[node]){
            if(!vis[a]){
                vis[a]=1;
                q.push(a);
                p[a]=node;
            }
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
            vis[i]=0;
        }

        int tot=0;

        for(int i=1; i<=n; i++) cin>>a[i], tot+=a[i];

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

        bfs();

        reverse(v.begin(),v.end());

        int ans=0;

        for(int b : v){
            if(a[b]){
                ans++;
                a[b]=0;
                a[p[b]]^=1;
            }
        }

        cout<<ans<<'\n';

    }
    
    return 0;
}