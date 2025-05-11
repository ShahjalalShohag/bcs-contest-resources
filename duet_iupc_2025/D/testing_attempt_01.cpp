#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

using LL = long long;



void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int i, n;
    string str;
    cin >> n >> str;

    vector<int> seen(26);
    for(char c: str)
    {
        i = c - 'a';

        if(seen[i])
        {
            cout << "NO";
            return;
        }

        seen[i] = 1;
    }

    cout << "YES";
}

signed main()
{
    pre();

    int tc, tt = 1;
    cin >> tt;
    
    for(tc = 1; tc <= tt; tc++)
    {
        // cout << "Case " << tc << ": ";
        solve(tc);
        cout << endl;
    }

    return 0;
}