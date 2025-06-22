#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vll = vector<ll>;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

const int MAXN = 2e7 + 5;
bool is_prime[MAXN];
int primes[MAXN], prime_cnt;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

const int MOD1 = 998244353; // 2^23 * 7 * 17 + 1
const int MOD2 = 1004535809; // 2^21 * 479 + 1
const int G1 = 3;
const int G2 = 3;

void gen_primes() {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;
    prime_cnt = 0;
    for (int i = 2; i < MAXN && prime_cnt < 1000010; ++i) {
        if (is_prime[i]) {
            primes[prime_cnt++] = i;
            for (ll j = 1LL * i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int powmod(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = int(1LL * res * a % mod);
        a = int(1LL * a * a % mod);
        b >>= 1;
    }
    return res;
}

void ntt(vector<int>& a, int mod, int g, bool invert) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? powmod(g, mod-1-(mod-1)/len, mod) : powmod(g, (mod-1)/len, mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len/2; ++j) {
                int u = a[i+j], v = int(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u+v < mod ? u+v : u+v-mod;
                a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
                w = int(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int nrev = powmod(n, mod-2, mod);
        for (int& x : a) x = int(1LL * x * nrev % mod);
    }
}

vector<int> square_polynomial(vector<int> a, int mod, int g) {
    int n = 1;
    while (n < 2 * sz(a)) n <<= 1;  // need space for degree up to 2n-2
    a.resize(n);
    
    // Single NTT transform
    ntt(a, mod, g, false);
    
    // Square each coefficient
    for (int i = 0; i < n; ++i) {
        a[i] = int(1LL * a[i] * a[i] % mod);
    }
    
    // Inverse NTT
    ntt(a, mod, g, true);
    return a;
}

vector<pair<ll, ll>> gen(const vi& pmap, int n) {
    auto res1 = square_polynomial(pmap, MOD1, G1);
    auto res2 = square_polynomial(pmap, MOD2, G2);
    
    // Circular wrap: add coefficients >= n to (i % n)
    for (int i = n; i < sz(res1); ++i) {
        res1[i % n] = (res1[i % n] + res1[i]) % MOD1;
        res2[i % n] = (res2[i % n] + res2[i]) % MOD2;
    }
    
    // Get coefficients at indices 2*i % n
    vector<pair<ll, ll>> hashes;
    for (int i = 0; i < n; ++i) {
        int idx = (2 * i + 1) % n;
        hashes.emplace_back(res1[idx], res2[idx]);
    }
    return hashes;
}

int main() {
    fastio();
    gen_primes();
    
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi a(n), b(n);
        for (int& x : a) cin >> x;
        for (int& x : b) cin >> x;
        vi pmap_a(n), pmap_b(n);
        for (int i = 0; i < n; ++i) {
            pmap_a[i] = primes[a[i] - 1];
            pmap_b[i] = primes[b[i] - 1];
        }
        auto ha = gen(pmap_a, n);
        auto hb = gen(pmap_b, n);

        map<pair<ll, ll>, int> cnt_a, cnt_b;
        for (auto& h : ha) cnt_a[h]++;
        for (auto& h : hb) cnt_b[h]++;
        
        // for (auto& [h, ca] : cnt_a) {
        //     cout << h.first << ' ' << h.second << ' ' << ca << '\n';
        // }

        // for (auto& [h, cb] : cnt_b) {
        //     cout << h.first << ' ' << h.second << ' ' << cb << '\n';
        // }

        ll ans = 0;
        for (auto& [h, ca] : cnt_a) {
            if (cnt_b.count(h)) ans += 1LL * ca * cnt_b[h];
        }
        cout << ans << '\n';
    }
    return 0;
}
