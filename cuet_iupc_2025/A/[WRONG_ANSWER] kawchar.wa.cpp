#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 200005

typedef long long ll;

void solve() {
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;
    if((n * m) % 2 == 1 || ((r2 + r1) % 2 == (c2 + c1) % 2)) cout << "NO\n";
    else cout << "YES\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}