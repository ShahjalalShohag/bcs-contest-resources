#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2) result = (1LL * result * base) % mod;
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool is_valid(const vector<int>& perm, const vector<int>& p) {
    int n = perm.size();
    for (int i = 1; i < n; ++i) {
        if (!(perm[i] < perm[p[i]])) return false;
    }
    return true;
}

int solve_case(int n, const vector<int>& a, const vector<int>& b) {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0); 

    int cnta = 0, cntb = 0;

    do {
        if (is_valid(perm, a)) cnta++;
        if (is_valid(perm, b)) cntb++;
    } while (next_permutation(perm.begin(), perm.end()));

    if (cntb == 0) return 0;
    int inv = mod_pow(cntb, MOD - 2, MOD);
    return (1LL * cnta * inv) % MOD;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] != -1) a[i]--; 
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            if (b[i] != -1) b[i]--; 
        }
        
        cout << solve_case(n, a, b) << "\n";
    }
    return 0;
}
