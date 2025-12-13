#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;

bool isEven(int x)
{
    return (x & 1) == 0;
}



void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;

    if(n > m)
    {
        swap(n, m);
        swap(r1, c1);
        swap(r2, c2);
    }

    if(n * m % 2 == 1)
    {
        cout << "NO";
        return;
    }

    if(n == 1)
    {
        if(c1 > c2) swap(c1, c2);

        if(isEven(c1 - 1) and isEven(c2 - c1 - 1) and isEven(m - c2)) cout << "YES";
        else cout << "NO";

        return;
    }

    if(isEven(r2 - r1 + c2 - c1)) cout << "NO";
    else cout << "YES";
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