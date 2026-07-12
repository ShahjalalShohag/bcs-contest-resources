#include<bits/stdc++.h>
using namespace std;

const int N = 2e6 + 9;
using ll = long long;

int tau2[N]; // tau2[n] = number of divisors of n^2
ll ans[N];
int spe[N]; // exponent of the smallest prime factor of n
bool flag[N];
vector<int> primes;

void precompute() {
    tau2[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!flag[i]) { 
            primes.push_back(i); 
            spe[i] = 1; 
            tau2[i] = 3; 
        }
        for (int p : primes) {
            ll ip = (ll)i * p;
            if (ip >= N) break;
            int j = (int)ip;
            flag[j] = 1;
            if (i % p == 0) {
                spe[j] = spe[i] + 1;
                tau2[j] = tau2[i] / (2 * spe[i] + 1) * (2 * spe[i] + 3);
                break;
            } else {
                spe[j] = 1;
                tau2[j] = tau2[i] * 3;
            }
        }
    }
    for (int b = 2; b < N; b++) ans[b] = ans[b - 1] + (tau2[b] - 1) / 2;
}

void solve() {
    int n;
    cin >> n;
    cout << ans[n] << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    precompute();
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
