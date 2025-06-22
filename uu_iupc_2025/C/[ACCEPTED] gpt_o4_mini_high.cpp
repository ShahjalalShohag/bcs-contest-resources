#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 1'000'000;
static const int MOD  = 998244353;

// fact[i] = i! % MOD
// invfact[i] = (i!)^{-1} % MOD
static int fact[MAXN+1], invfact[MAXN+1];
// prefixXor[n] = XOR_{k=1..n} g(k)
static uint32_t prefixXor[MAXN+1];

// fast exponentiation mod
long long modexp(long long a, long long e=MOD-2) {
    long long r = 1 % MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Precompute factorials and inverse factorials up to MAXN
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++){
        fact[i] = int((long long)fact[i-1] * i % MOD);
    }
    invfact[MAXN] = int(modexp(fact[MAXN])); 
    for(int i = MAXN; i >= 1; i--){
        // invfact[i-1] = invfact[i] * i^{-1} mod M
        invfact[i-1] = int((long long)invfact[i] * i % MOD);
    }

    // 2) Build prefixXor array
    prefixXor[0] = 0;
    for(int k = 1; k <= MAXN; k++){
        uint32_t gk;
        if (k & 1) {
            // k odd -> XOR of row except C(k,0) = 1
            gk = 1;
        } else {
            // k even -> s(k) = C(k, k/2) % MOD
            int half = k >> 1;
            int c = int(
                (long long)fact[k]
                * invfact[half] % MOD
                * invfact[half] % MOD
            );
            // g(k) = s(k) XOR 1
            gk = (uint32_t)c ^ 1u;
        }
        prefixXor[k] = prefixXor[k-1] ^ gk;
    }

    // 3) Answer queries
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        cout << prefixXor[n] << '\n';
    }
    return 0;
}
