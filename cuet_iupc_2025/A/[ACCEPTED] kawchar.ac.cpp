#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 200005

typedef long long ll;

bool ok(int c1, int c2) {
    if(c2 < c1) swap(c1, c2);
    return (c1 % 2 == 1) && (c2 % 2 == 0); 
}

void solve() {
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;
    if((n * m) % 2 == 1 || ((r2 + r1) % 2 == (c2 + c1) % 2) || (n == 1 && !ok(c1, c2)) || (m == 1 && !ok(r1, r2))) cout << "NO\n";
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