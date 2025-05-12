#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());

        // prefix XOR and OR
        vector<ll> px(n), po(n);
        px[0] = a[0];
        po[0] = a[0];
        for(int i = 1; i < n; i++){
            px[i] = px[i-1] ^ a[i];
            po[i] = po[i-1] | a[i];
        }
        // suffix XOR and OR
        vector<ll> sx(n), so(n);
        sx[n-1] = a[n-1];
        so[n-1] = a[n-1];
        for(int i = n-2; i >= 0; i--){
            sx[i] = sx[i+1] ^ a[i];
            so[i] = so[i+1] | a[i];
        }

        ll ans = LLONG_MAX;
        // try splitting at i: 1..min(n-1,31)
        int LIM = min(n-1, 31);
        for(int i = 1; i <= LIM; i++){
            // Case 1: s1 = first i elements, s2 = rest
            ll x1 = px[i-1];
            ll y1 = so[i];
            ans = min(ans, x1 * y1);

            // Case 2: s2 = first i elements, s1 = rest
            ll y2 = po[i-1];
            ll x2 = sx[i];
            ans = min(ans, x2 * y2);
        }

        cout << ans << "\n";
    }

    return 0;
}
