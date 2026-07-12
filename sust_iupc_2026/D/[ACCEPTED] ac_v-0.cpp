#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int query(ll M, ll V) {
    cout << "? " << M << ' ' << V << endl;

    int r;
    if (!(cin >> r)) {
        exit(0);
    }

    return r;
}

void solve() {
    ll difference = 0;

    for (int bit = 0; bit < 60; bit++) {
        ll value = 1LL << bit;

        if (query(value, 0) == 1) {
            difference |= value;
        }
    }

    int pivot = -1;

    for (int bit = 59; bit >= 0; bit--) {
        if (difference & (1LL << bit)) {
            pivot = bit;
            break;
        }
    }

    ll A = 0;
    ll pivotValue = 1LL << pivot;

    for (int bit = 0; bit < 60; bit++) {
        if (bit == pivot) {
            continue;
        }

        ll bitValue = 1LL << bit;
        ll mask = pivotValue | bitValue;

        if (query(mask, 0) == 0) {
            A |= bitValue;
        }
    }

    ll B = A ^ difference;

    cout << "! " << A << ' ' << B << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        solve();
    }

    return 0;
}