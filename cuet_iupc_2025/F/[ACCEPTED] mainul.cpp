#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
long long Power(long long a, long long b)
{
    long long res = 1;
    a = a % MOD;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
long long ModInverse(long long a)
{
    return Power(a, MOD - 2);
}
void solve()
{
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    long long sum = 0;
    for (auto i : v)
        (sum += i) %= MOD;

    long long all_sum = 0;

    for (int i = 0; i < n - 1; i++)
    {
        sum = (sum - v[i] + MOD) % MOD;
        all_sum += (MOD + sum - ((long long)(n - i - 1) * v[i]) % MOD) % MOD;
        all_sum %= MOD;
    }

    cout << 2 * all_sum % MOD * ModInverse(n) % MOD << "\n";

    return;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}