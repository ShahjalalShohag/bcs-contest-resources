// Maximum number of odd blocks: largest p (with p == k mod 2) of odd blocks that
// can still hold exactly k tokens; capacity bound flips with the parity of m.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);

        long long hi = min(n, k);                 // need >= p tokens, and p <= n
        if (m % 2 == 0) hi = min(hi, n * m - k);   // m even: each odd block wastes 1 capacity

        long long p = hi - ((hi - k) & 1);         // largest value <= hi with p == k (mod 2)
        if (p < 0) p = 0;
        printf("%lld\n", p);
    }
    return 0;
}
