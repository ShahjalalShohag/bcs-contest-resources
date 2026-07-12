#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2000006;
int spf[N];
long long pre[N];

void sieve() {
    for(int i = 0; i < N; i++) spf[i] = i;
    for(int i = 2; i < N; i++) {
        if(spf[i] == i) {
            for(int j = i; j < N; j += i) {
                spf[j] = i;
            }
        }
    }
}

void preCalc() {
    for(int i = 2; i < N; i++) {
        pre[i] = pre[i - 1];
        int num = i, ans = 1;
        while(num > 1) {
            int x = spf[num], cnt = 0;
            while(num % x == 0) {
                cnt += 1;
                num /= x;
            }

            ans *= (2 * cnt + 1);
        }
        ans = (ans - 1) / 2;
        pre[i] += ans;
    }
}
void solve() {
    int n;
    cin >> n;
    cout << pre[n] << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    sieve();
    preCalc();

    int t = 1;
    cin >> t;
    
    while(t--){
        solve();
    }

    return 0;
}