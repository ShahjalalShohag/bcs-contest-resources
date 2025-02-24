#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    if (n == 1) {
    	cout << "1\n";
    	return;
    }
    
    int last = n / 2 + 1;
    cout << 1;
    for(int i = n; i > 1; i--) {
    	if(i == last) continue;
    	cout << " " << i;
    }
    cout << " " << last << "\n";
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