#include <bits/stdc++.h>
using namespace std;

int spf[10000001];

void sieve() {
    int maxN = 10000000;
    for (int i = 1; i <= maxN; i++) spf[i] = i;

    for (int i = 2; 1LL * i * i <= maxN; i++) {
        if (spf[i] == i) {
            for (int j = 1LL * i * i; j <= maxN; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    while (n > 1) {
        int p = spf[n];
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        factors.push_back({p, cnt});
    }
    return factors;
}

void divs(vector<int> &divisors, vector<pair<int, int>> &factors, int pos, int mul) {
    if (pos == factors.size()) {
        divisors.push_back(mul);
        return;
    }
    divs(divisors, factors, pos + 1, mul);
    int p = factors[pos].first;
    int cnt = factors[pos].second;
    for (int i = 1; i <= cnt; i++) {
        mul *= p;
        divs(divisors, factors, pos + 1, mul);
    }
}

vector<int> findDivs(int n) {
    vector<pair<int, int>> factors = factorize(n);
    vector<int> divisors;
    divs(divisors, factors, 0, 1);
    return divisors;
}

vector<int> counter(10000001, 0);

void solve() {
    long long n; cin >> n;
    vector<int> a(n + 1);
    long long oneCount = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];       
        if (a[i] == 1) oneCount++;
    }
    sort(a.begin() + 1, a.end());

    vector<pair<int, int>> sortedInput;

    for (int i = 1; i <= n; i++) {
        if (sortedInput.empty() || sortedInput.back().first != a[i]) {
            sortedInput.push_back({a[i], 1});
        } else {
            sortedInput.back().second++;
        }
    }
    
    for (auto x: sortedInput) {
        vector<int> divs = findDivs(x.first);
        for (auto y: divs) {
            counter[y] += x.second; 
        }
    }
    
    long long ans = 0;

    for (auto x: sortedInput) {
        for (int d : findDivs(x.first)) {
            counter[d] -= x.second;
        }
        
        vector<pair<int, int>> factors = factorize(x.first);
        vector<pair<int, int>> temp;
        for (auto [p, cnt] : factors) {
            int lim = (cnt / 2) + 1;
            int val = 1;
            for (int i = 0; i < lim; i++) {
                val *= p;
            }
            temp.push_back({val, lim});
        }

        int sz = temp.size();
        long long cnt = 0;
        for (int mask = 1; mask < (1LL << sz); mask++) {
            int sign = 0;
            int tmp = 1;
            for (int j = 0; j < sz; j++) {
                if (mask & (1LL << j)) {
                    tmp *= temp[j].first;
                    sign++;
                }
            }
            if (sign % 2 == 0) {
                cnt -= counter[tmp];
            } else {
                cnt += counter[tmp];
            }
        }
        ans += cnt * x.second;
    }
    long long ans1 = 0;
    long long sum = 0;
    for (auto x: sortedInput) {
        sum += x.second;
    }
    for (auto x: sortedInput) {
        sum -= x.second;
        ans1 += sum * x.second;
    }
    ans = ans1 - ans;
    ans += (oneCount * (oneCount + 1)) / 2;
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t; cin >> t;
    sieve();
    while (t--) {
        solve();
    }
}