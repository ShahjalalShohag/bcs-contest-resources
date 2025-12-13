#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if ((a[0] == 1 && a[n - 1] == 2) || (a[0] == 2 && a[n - 1] == 1))
        cout << "YES \n\t   \n\t\n\n\n\n\n\n\n\n";
    else
        cout << "NO \t \t \t \t \t \t \t \t \t \t \t \n \t \n \t \n \t \n \t \n \t \n \t \n \t";

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