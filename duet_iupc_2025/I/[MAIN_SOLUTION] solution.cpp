#include <bits/stdc++.h>
using namespace std;

#define ll long long int

int main()
{

    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        scanf("%d", &n);
        int a[n];
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        ll ans = 0;
        if(n <= 20) {
            ans = 1e15;
            int max_mask = (1 << n) - 1;
            for(int i = 1; i < max_mask; i++) {
                int _xor = 0, _or = 0;
                for(int j = 0; j < n; j++) {
                    if(i & (1 << j)) _xor ^= a[j];
                    else _or |= a[j];
                }
                ans = min(ans, (ll)_xor * (ll)_or);
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}