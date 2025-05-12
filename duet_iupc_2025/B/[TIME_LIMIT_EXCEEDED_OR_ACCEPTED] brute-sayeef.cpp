#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 300005

int n, a[mxn], a2[mxn], p[mxn], vis[mxn];
vector<int>g[mxn], v;

void bfs(int j){
    v.clear();
    for(int i=0; i<n+2; i++) vis[i]=0;

    queue<int>q;
    vis[j]=1;
    q.push(j);

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
        }

        int tot=0;

        for(int i=1; i<=n; i++) cin>>a2[i], tot+=a2[i];

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

        int ans=INT_MAX;

        for(int j=1; j<=n; j++){

            for(int i=1; i<=n; i++) a[i]=a2[i];

            bfs(j);

            reverse(v.begin(),v.end());

            int now=0;

            for(int b : v){
                if(a[b]){
                    now++;
                    a[b]=0;
                    a[p[b]]^=1;
                }
            }

            if(ans!=INT_MAX) assert(ans==now);

            ans=min(ans,now);

        }

        cout<<ans<<'\n';

    }
    
    return 0;
}