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
    ll diff = 0;

    for (int bit = 0; bit < 60; bit++) {
        ll mask = 1LL << bit;

        if (query(mask, mask) == 1) {
            diff |= mask;
        }
    }

    int pivot = __builtin_ctzll(diff);

    ll first = 0;

    for (int bit = 0; bit < 60; bit++) {
        if (bit == pivot) {
            continue;
        }

        ll pivotMask = 1LL << pivot;
        ll bitMask = 1LL << bit;

        ll M = pivotMask | bitMask;
        ll V = bitMask;

        if (query(M, V) == 1) {
            first |= bitMask;
        }
    }

    ll second = first ^ diff;

    if (first > second) {
        swap(first, second);
    }

    cout << "! " << first << ' ' << second << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;

    for (int cs = 1; cs <= TC; cs++) {
        // cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}