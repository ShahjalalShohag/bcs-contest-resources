#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vll = vector<ll>;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

ull my_pow(ull a, ull b) {
    ull res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// Optimized Karatsuba multiplication for polynomials
vector<ull> karatsuba(const vector<ull>& a, const vector<ull>& b) {
    int n = sz(a);
    if (n <= 32) {
        vector<ull> res(2 * n - 1);
        // Unrolled loop for better performance
        for (int i = 0; i < n; i += 4) {
            for (int j = 0; j < n; j += 4) {
                // Process 4x4 block at a time
                for (int ii = i; ii < min(i + 4, n); ++ii) {
                    for (int jj = j; jj < min(j + 4, n); ++jj) {
                        res[ii + jj] += a[ii] * b[jj];
                    }
                }
            }
        }
        return res;
    }

    int k = n / 2;
    vector<ull> res(2 * n - 1);
    vector<ull> temp(k);  // Reusable temporary vector

    // Compute a1*b1 and a2*b2
    vector<ull> a1b1 = karatsuba(vector<ull>(a.begin(), a.begin() + k),
                                vector<ull>(b.begin(), b.begin() + k));
    vector<ull> a2b2 = karatsuba(vector<ull>(a.begin() + k, a.end()),
                                vector<ull>(b.begin() + k, b.end()));

    // Compute (a1+a2)*(b1+b2) using the same temporary vector
    for (int i = 0; i < k; ++i) {
        temp[i] = a[i] + (i + k < n ? a[i + k] : 0);
    }
    vector<ull> a1_plus_a2 = temp;
    
    for (int i = 0; i < k; ++i) {
        temp[i] = b[i] + (i + k < n ? b[i + k] : 0);
    }
    vector<ull> b1_plus_b2 = temp;

    vector<ull> sum = karatsuba(a1_plus_a2, b1_plus_b2);

    // Copy results into final vector
    for (int i = 0; i < sz(a1b1); ++i) {
        res[i] = a1b1[i];
    }
    for (int i = 0; i < sz(a2b2); ++i) {
        res[i + 2 * k] = a2b2[i];
    }
    for (int i = 0; i < sz(sum); ++i) {
        res[i + k] += sum[i] - (i < sz(a1b1) ? a1b1[i] : 0) - (i < sz(a2b2) ? a2b2[i] : 0);
    }

    return res;
}

vector<ull> square_polynomial(vector<ull> a) {
    return karatsuba(a, a);
}

vector<ull> gen(const vector<ull>& pmap, int n) {
    vector<ull> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = pmap[i];
    }
    
    auto res = square_polynomial(a);
    
    // Circular wrap: add coefficients >= n to (i % n)
    for (int i = n; i < sz(res); ++i) {
        res[i % n] += res[i];
    }
    
    // Get coefficients at indices 2*i % n
    vector<ull> hashes;
    for (int i = 0; i < n; ++i) {
        int idx = (2 * i + 1) % n;
        hashes.push_back(res[idx]);
    }
    return hashes;
}

int main() {
    fastio();
    
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi a(n), b(n);
        for (int& x : a) cin >> x;
        for (int& x : b) cin >> x;
        
        vector<ull> pmap_a(n), pmap_b(n);
        for (int i = 0; i < n; ++i) {
            pmap_a[i] = my_pow(35, my_pow(57, a[i]) * a[i]);
            pmap_b[i] = my_pow(35, my_pow(57, b[i]) * b[i]);
        }
        
        auto ha = gen(pmap_a, n);
        auto hb = gen(pmap_b, n);

        map<ull, int> cnt_a, cnt_b;
        for (auto& h : ha) cnt_a[h]++;
        for (auto& h : hb) cnt_b[h]++;
    
        ll ans = 0;
        for (auto& [h, ca] : cnt_a) {
            if (cnt_b.count(h)) ans += 1LL * ca * cnt_b[h];
        }
        cout << ans << '\n';
    }
    return 0;
}
