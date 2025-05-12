#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        if (s == string(n, 'A') || s == string(n, 'B') || s == string(n, 'S')) {
            cout << 1 << endl;
            continue;
        }

        int litmus_papers = 0;
        char prev = '0'; // Initially no chemical
        for (int i = 0; i < n; ++i) {
            if (s[i] != prev) {  
                litmus_papers++;
                prev = s[i];
            }
        }

        cout << litmus_papers << endl;
    }

    return 0;
}
