#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;

const int N = 3e5 + 5;
vector<int> nbr[N];
int dist[N], vis[N];

void bfs(int src, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        vis[i] = 0;
        dist[i] = -1;
    }

    queue<int> q;

    dist[src] = 0;
    vis[src] = 1;
    q.push(src);

    while(!q.empty())
    {
        auto x = q.front();
        q.pop();

        for(auto y: nbr[x]) if(!vis[y])
        {
            dist[y] = dist[x] + 1;
            vis[y] = 1;
            q.push(y);
        }
    }
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

    bfs(c, n);

    if(dist[a] == -1 and dist[b] == -1)
    {
        bfs(a, n);

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