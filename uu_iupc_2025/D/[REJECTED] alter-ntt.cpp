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

vector<int> multiply(vector<int> a, vector<int> b, int mod, int g) {
    int n = 1;
    while (n < sz(a) + sz(b)) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, mod, g, false);
    ntt(b, mod, g, false);
    for (int i = 0; i < n; ++i) a[i] = int(1LL * a[i] * b[i] % mod);
    ntt(a, mod, g, true);
    return a;
}

vector<pair<ll, ll>> gen(const vi& pmap, int n) {
    vector<int> poly1_1(3*n), poly1_2(3*n);
    for (int i = 0; i < 3*n; ++i) {
        poly1_1[i] = pmap[i % n];
        poly1_2[i] = pmap[i % n];
    }
    vector<int> poly2_1(n), poly2_2(n);
    for (int i = 0; i < n; ++i) {
        poly2_1[i] = pmap[i];
        poly2_2[i] = pmap[i];
    }
    auto res1 = multiply(poly1_1, poly2_1, MOD1, G1);
    auto res2 = multiply(poly1_2, poly2_2, MOD2, G2);
    vector<pair<ll, ll>> hashes;
    for (int i = 0, idx = n-1; i < n; ++i, idx += 2) {
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
        ll ans = 0;
        for (auto& [h, ca] : cnt_a) {
            if (cnt_b.count(h)) ans += 1LL * ca * cnt_b[h];
        }
        cout << ans << '\n';
    }
    return 0;
}
