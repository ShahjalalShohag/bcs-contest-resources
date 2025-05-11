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
    int a = 0, b = 0, n;
    string s;
    cin >> n >> s;

    for(char c: s)
    {
        if(c == 'A') a++;
        else if(c == 'B') b++;
    }

    if(a == 0 and b == 0) cout << 2;
    else if(a > 0 and b > 0) cout << 1;
    else cout << a + b;
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
        cout << '\n';
    }

    return 0;
}