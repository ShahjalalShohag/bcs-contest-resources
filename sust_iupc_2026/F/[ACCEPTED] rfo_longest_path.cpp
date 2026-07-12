#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
using PII = pair<int,int>;
using III = tuple<int,int,int>;

const int N = 3e5 + 5;
vector<int> blackNeighbor[N], whiteNeighbor[N];

using Edge = III;
Edge allEdg[N];

bool vis[N];
void dfs(vector<int> neighbor[], int n, int x)
{
    if(vis[x]) return;
    vis[x] = 1;

    for(auto y: neighbor[x]) dfs(neighbor, n, y);
}

int inDeg[N];
vector<int> order;
void topSort(vector<int> neighbor[], int n)
{
    int x;
    for(x = 0; x < n; x++) if(vis[x]) inDeg[x] = 0;

    for(x = 0; x < n; x++) if(vis[x])
        for(auto y: neighbor[x]) if(vis[y]) inDeg[y]++;

    queue<int> q;
    q.push(0);

    while(!q.empty())
    {
        x = q.front();
        q.pop();
        order.push_back(x);

        for(auto y: neighbor[x])
        {
            inDeg[y]--;
            if(inDeg[y] == 0) q.push(y);
        }
    }
}

int dist[N];
void getDistance(vector<int> neighbor[], int n)
{
    int x, y;
    for(x = 0; x < n; x++) dist[x] = -1;

    dist[0] = 0;
    for(auto x: order)
        for(auto y: neighbor[x])
            dist[y] = max(dist[y], 1 + dist[x]);
}



void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int i, n, m;
    cin >> n >> m;

    for(i = 0; i < n; i++)
    {
        blackNeighbor[i].clear();
        whiteNeighbor[i].clear();
    }

    int a, b, c;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        a--, b--;

        allEdg[i] = {a, b, c};

        if(c) blackNeighbor[a].push_back(b);
        else whiteNeighbor[a].push_back(b);
    }

    for(i = 0; i < n; i++) vis[i] = 0;
    dfs(blackNeighbor, n, 0);

    if(!vis[n - 1])
    {
        cout << -1;
        return;
    }

    int k = 1;
    for(i = 0; i < n - 1; i++) if(vis[i])
    {
        k++;

        if(blackNeighbor[i].empty())
        {
            cout << -1;
            return;
        }
    }

    order.clear();
    topSort(blackNeighbor, n);

    if(order.size() != k)
    {
        cout << -1;
        return;
    }

    getDistance(blackNeighbor, n);
    for(auto x: order) if(dist[x] == -1)
    {
        cout << -1;
        return;
    }

    vector<int> ans;
    for(i = 0; i < m; i++)
    {
        auto [a, b, c] = allEdg[i];

        if(c)
        {
            if(!vis[a] or !vis[b])
            {
                cout << -1;
                return;
            }

            if(dist[b] <= dist[a])
            {
                cout << -1;
                return;
            }

            ans.push_back(dist[b] - dist[a]);
        }

        else ans.push_back(936000);
    }

    for(auto w: ans) cout << w * 125 << ' ';
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