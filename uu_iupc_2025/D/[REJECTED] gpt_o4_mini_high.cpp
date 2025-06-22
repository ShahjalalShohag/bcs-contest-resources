#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        // if the two multisets differ, no shifts can match
        if (a != b) {
            cout << 0 << "\n";
            continue;
        }

        // even n → group acts as full S_n → any two
        // shifts are equivalent ↔ multiset(a)=multiset(b)
        if (n % 2 == 0) {
            // all n choices of i times all n choices of j
            ll nn = n;
            cout << nn * nn << "\n";
        }
        else {
            // odd n: exactly one position (the center) is fixed;
            // the other n−1 positions form one orbit.
            // two shifts match iff they put the same element
            // into the center.  Over all i,j this contributes
            // sum_{v} freq(v)^2.
            ll ans = 0;
            for (int i = 0; i < n; ) {
                int j = i+1;
                while (j < n && a[j] == a[i]) j++;
                ll freq = j - i;
                ans += freq * freq;
                i = j;
            }
            cout << ans << "\n";
        }
    }
}
