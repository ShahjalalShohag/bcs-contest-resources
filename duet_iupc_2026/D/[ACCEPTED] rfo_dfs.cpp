#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
 
const int N = 3e5 + 5;
vector<int> nbr[N];
int dist[N];
 
void dfs(int src, int par)
{
    dist[src] = par >= 0? dist[par] + 1: 0;
 
    for(auto nxt: nbr[src]) if(nxt != par) dfs(nxt, src);
}
 
 
 
void pre()
{
    fastio;
 
    
}
 
void solve(int tc)
{
    int i, n, m, a, b, c;
    cin >> n >> m >> a >> b >> c;
    a--, b--, c--;
 
    for(i = 0; i < n; i++) nbr[i].clear();
 
    int u, v;
    for(i = 0; i < m; i++)
    {
        cin >> u >> v;
        u--, v--;
 
        nbr[u].push_back(v);
        nbr[v].push_back(u);
    }
 
    for(i = 0; i < n; i++) dist[i] = -1;
    dfs(c, -1);
 
    if(dist[a] == -1 and dist[b] == -1)
    {
        dfs(a, -1);
 
        if(dist[b] == -1) cout << "Tie";
        else cout << "Alice";
 
        return;
    }
 
    if(dist[a] == -1) dist[a] = 1;
    else if(dist[b] == -1) dist[b] = dist[a] + 1;
 
    if(dist[a] < dist[b]) cout << "Alice";
    else if(dist[a] > dist[b]) cout << "Bob";
    else cout << "Tie";
}
 
int main()
{
    pre();
 
    int tc, tt = 1;
    cin >> tt;
    
    for(tc = 1; tc <= tt; tc++)
    {
        // cout << "Case " << tc << ": ";
        solve(tc);
        cout << '\n';
    }
 
    return 0;
}