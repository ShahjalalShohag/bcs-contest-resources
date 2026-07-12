#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;
using PLL = pair<LL,LL>;
using PLB = pair<LL,bool>;
 
const LL MOD = 998244353;
 
LL binExp(LL a, LL p)
{
    LL ans = 1;
 
    while(p > 0)
    {
        if(p % 2 == 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD;
        p /= 2;
    }
 
    return ans;
}
 
 
LL boundedTotient(vector<LL>& p, LL cap)
{
    int i, k = p.size();
    LL temp, ans = 0, cnt;
 
    int mask, m = 1 << k;
    for(mask = 0; mask < m; mask++)
    {
        temp = 1;
        for(i = 0; i < k; i++) if(mask & (1 << i))
        {
            if(p[i] <= cap / temp) temp *= p[i];
            else temp = cap + 1;
        }
 
        cnt = cap / temp;
        __builtin_popcount(mask) & 1? ans -= cnt: ans += cnt;
    }
 
    return ans;
}
 
 
 
void pre()
{
    fastio;
 
    
}
 
void solve(int tc)
{
    LL n;
    int i, k, m;
    cin >> n >> k;
 
    vector<LL> p(k);
    for(auto &x: p) cin >> x;

    cin >> m;
    vector<PLB> color(m);
    for(auto &[x, c]: color) cin >> x >> c;

    for(auto &[x, c]: color) for(auto y: p) while(x % y == 0)
    {
        x /= y;
        c ^= 1;
    }
    sort(color.begin(), color.end());

    LL t = boundedTotient(p, n);

    int block = m;
    for(i = 1; i < m; i++)
    {
        auto [x0, c0] = color[i - 1];
        auto [x1, c1] = color[i];

        if(x0 == x1 and c0 != c1)
        {
            cout << 0;
            return;
        }

        if(x0 == x1) block--;
    }

    cout << binExp(2, t - block);
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