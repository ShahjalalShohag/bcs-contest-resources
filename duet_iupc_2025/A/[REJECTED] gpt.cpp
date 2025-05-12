#include <bits/stdc++.h>
using namespace std;
int MOD = 998244353;

// fast exponentiation modulo
long long modpow(long long a, long long e=MOD-2){
    long long r=1;
    while(e){
        if(e&1) r = r*a % MOD;
        a = a*a % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<int> qs(T);
    vector<int> ms(T);
    int Nmax = 0;
    for(int i=0;i<T;i++){
        cin >> qs[i] >>ms[i];
        Nmax = max(Nmax, qs[i]);
    }

    // Precompute up to Nmax
    vector<long long> fact(2*Nmax+1, 1), inv2(Nmax+1,1), oddH(Nmax+1,0);
    // factorials: fact[k] = k! mod MOD
    for(int i=1; i<=2*Nmax; i++){
        fact[i] = fact[i-1]*i % MOD;
    }
    // inv2[k] = (1/2)^k mod MOD
    long long inv_2 = modpow(2);
    for(int i=1; i<=Nmax; i++){
        inv2[i] = inv2[i-1] * inv_2 % MOD;
    }
    // precompute modular inverses of odd numbers up to 2*Nmax-1
    vector<long long> invOdd(2*Nmax+1, 0);
    for(int x=1; x<=2*Nmax; x+=2){
        invOdd[x] = modpow(x);
    }
    // build odd‐harmonic sums: H[k] = sum_{j=1..k} 1/(2j-1)
    for(int k=1; k<=Nmax; k++){
        oddH[k] = (oddH[k-1] + invOdd[2*k-1]) % MOD;
    }

    // answer each query
    // total_perms = (2n)!/2^n  -> fact[2n]*inv2[n]
    // answer = total_perms * oddH[n] mod
    int i=0;
    for(int n: qs){
        MOD=ms[i];
        i++;
        long long total = fact[2*n] * inv2[n] % MOD;
        long long ans = total * oddH[n] % MOD;
        cout << ans << "\n";
    }
    return 0;
}
