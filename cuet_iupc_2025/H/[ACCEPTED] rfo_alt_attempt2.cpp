#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;

using Point = pair<int,int>;
using Triangle = array<Point,3>;
using TII = tuple<int,int,int>;

const int N = 2e7 + 5;
int spf[N];

vector<int> twinPrimeL;

void Sieve()
{
    int i, j;
    for(i = 0; i < N; i++) spf[i] = i;

    for(i = 2; i < N; i++) if(spf[i] == i)
    {
        for(j = i; j < N; j += i) if(spf[j] == j)
        {
            spf[j] = i;
        }
    }
}

void initTwinPrimes()
{
    int i;

    for(i = 7; i < N; i += 6)
        if(spf[i] == i and spf[i - 2] == i - 2)
            twinPrimeL.push_back(i - 2);
}



void pre()
{
    fastio;

    Sieve();
    initTwinPrimes();
}

void solve(int tc)
{
    int i, n;
    cin >> n;

    vector<Point> points;
    vector<TII> triangles;

    points.push_back({0, 0});
    points.push_back({2, 0});
    points.push_back({0, 2});
    points.push_back({-2, -2});
    points.push_back({0, -2});
    points.push_back({-2, 0});

    for(i = 0; triangles.size() < n; i += 2)
    {
        points.push_back({twinPrimeL[i], twinPrimeL[i + 1]});

        triangles.push_back({points.size(), 1, 2});
        triangles.push_back({points.size(), 1, 3});
        triangles.push_back({points.size(), 4, 5});
        triangles.push_back({points.size(), 4, 6});
    }
    while(triangles.size() > n) triangles.pop_back();

    cout << points.size() << '\n';
    for(auto [x, y]: points) cout << x + 2 << ' ' << y + 2 << '\n';

    for(auto [a, b, c]: triangles) cout << a << ' ' << b << ' ' << c << '\n';
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