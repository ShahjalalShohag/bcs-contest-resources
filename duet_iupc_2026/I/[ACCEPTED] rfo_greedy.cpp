#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
using PII = pair<int,int>;

const int N = 1005;
PII board[N], color[N];
int paint[N][N];



void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int i, n;
    cin >> n;

    for(i = 0; i < n; i++)
    {
        cin >> board[i].first;
        board[i].second = i;
    }

    for(i = 0; i < n; i++)
    {
        cin >> color[i].first;
        color[i].second = i;
    }

    sort(board, board + n);
    sort(color, color + n, greater<PII>());

    int b, c, k;

    for(b = 0; b < n; b++) for(c = 0; c < n; c++) paint[b][c] = 0;

    b = 0, c = 0;
    while(b < n)
    {
        k = min(board[b].first, color[c].first);
        paint[board[b].second][color[c].second] = k;

        board[b].first -= k;
        color[c].first -= k;
        
        if(board[b].first == 0) b++;
        if(color[c].first == 0) c++;
    }

    for(b = 0; b < n; b++)
    {
        for(c = 0; c < n; c++) cout << paint[b][c] << " \n"[c == n - 1];
    }

    for(b = 0; b < n; b++) cout << board[b].second + 1 << " \n"[b == n - 1];
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
        // cout << '\n';
    }

    return 0;
}