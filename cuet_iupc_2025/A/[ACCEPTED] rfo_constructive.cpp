#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
using PII = pair<int,int>;
 
 
 
void pre()
{
    fastio;
 
    
}
 
void solve(int tc)
{
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;
 
    if(n % 2 == 1)
    {
        swap(n, m);
        swap(r1, c1);
        swap(r2, c2);
    }
 
    if(n % 2 == 1)
    {
        cout << "NO";
        return;
    }

    int i, j, s = n * m;
    vector<vector<int>> grid(n, vector<int>(m));
    vector<PII> circuit;

    r1--, c1--, r2--, c2--;
    grid[r1][c1] = 1;
    grid[r2][c2] = 1;

    for(j = 0; j < m; j++) circuit.push_back({n - 1, j});
    for(i = n - 2; i >= 0; i--) circuit.push_back({i, m - 1});
    for(j = m - 2; j >= 0; j--) circuit.push_back({0, j});

    for(i = 1; i < n - 1; i++)
    {
        if(i % 2 == 1)
        {
            for(j = 0; j < m - 1; j++)
                circuit.push_back({i, j});
        }

        else
        {
            for(j = m - 2; j >= 0; j--)
                circuit.push_back({i, j});
        }
    }

    int d;

    if(n == 1 or m == 1) d = -1;
    else
    {
        for(i = 0; i < s; i++)
        {
            auto [x, y] = circuit[i];

            if(grid[x][y] == 1)
            {
                d = i;
                break;
            }
        }
    }

    for(i = 0; i < s; i += 2)
    {

        auto [x1, y1] = circuit[(d + i + 1) % s];
        auto [x2, y2] = circuit[(d + i + 2) % s];


        if(grid[x1][y1] == 1)
        {
            i--;
            continue;
        }

        if(grid[x2][y2] == 1)
        {
            cout << "NO";
            return;
        }
    }

    cout << "YES";
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