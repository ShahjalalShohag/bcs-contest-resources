#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

u64 mul_mod(u64 a, u64 b, u64 mod) { return (u128)a * b % mod; }
u64 pow_mod(u64 a, u64 d, u64 mod) {
    u64 r = 1;
    while (d) {
        if (d & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return r;
}
bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL})
        if (n % p == 0) return n == p;
    u64 d = n - 1; int s = 0;
    while ((d & 1) == 0) d >>= 1, ++s;
    for (u64 a : {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

inline ll doubled_area(const pair<int,int>& A,
                       const pair<int,int>& B,
                       const pair<int,int>& C) {
    ll dx1 = (ll)B.first - A.first;
    ll dy1 = (ll)B.second - A.second;
    ll dx2 = (ll)C.first - A.first;
    ll dy2 = (ll)C.second - A.second;
    ll det = dx1 * dy2 - dx2 * dy1;
    return det < 0 ? -det : det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    const int COORD_MAX = 10000000;
    const ll TOTAL_LIMIT = 1e6;
    const ll MAX_TRY = 1e5;

    ll rem = TOTAL_LIMIT;
    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> coord(0, COORD_MAX);

    while (T--) {
        int N; cin >> N;

        if (N == 1) {
            cout << 3 << "\n0 0\n2 0\n0 2\n1 2 3\n";
            continue;
        }

        ll n3 = 1LL * N * N * N;
        ll total_try = min({n3, rem, MAX_TRY});
        if (total_try < 1) total_try = 1;

        const int SET_TRIES = 50;
        ll per_set = max(1LL, total_try / SET_TRIES);

        int K = (N + 3) / 4 + 6;

        bool ok = false;
        vector<pair<int,int>> bestP;                     // best pointset found so far
        vector<tuple<int,int,int>> bestT;                // best triangles found so far
        size_t best_count = 0;                           // how many triangles in bestT

        for (int s = 0; s < SET_TRIES && rem > 0 && !ok; s++) {

            // generate K distinct points
            vector<pair<int,int>> P;
            P.reserve(K);
            unordered_set<u64> vis;
            vis.reserve(K*2);

            while ((int)P.size() < K) {
                int x = coord(rng), y = coord(rng);
                u64 key = ((u64)x << 32) ^ (u64)y;
                if (vis.insert(key).second) P.push_back({x,y});
            }

            // combinations count = C(K,3)
            ll comb = (ll)K * (K - 1) * (K - 2) / 6;

            unordered_set<u64> used_area;
            used_area.reserve(N*2);
            vector<tuple<int,int,int>> tris;
            tris.reserve(N);

            if (comb <= total_try && comb <= rem) {
                // full enumeration
                ll tested = 0;
                for (int i = 0; i < K && (int)tris.size() < N; i++) {
                    for (int j = i+1; j < K && (int)tris.size() < N; j++) {
                        for (int k = j+1; k < K && (int)tris.size() < N; k++) {
                            tested++;
                            ll da = doubled_area(P[i],P[j],P[k]);
                            if (da == 0 || (da & 1)) continue;
                            ll area = da >> 1;
                            if (area <= 1) continue;
                            if (!isPrime(area)) continue;
                            if (used_area.count(area)) continue;
                            used_area.insert(area);
                            tris.emplace_back(i+1,j+1,k+1);
                        }
                    }
                }
                rem -= min(rem, tested);

                // update best if this pointset gave more valid triangles
                if (tris.size() > best_count) {
                    best_count = tris.size();
                    bestP = P;            // copy points
                    bestT = tris;         // copy triangles
                }

                if ((int)tris.size() == N) {
                    ok = true;
                    // bestP/bestT already set by move if preferred; but we already stored
                }
            } else {
                // random sampling
                uniform_int_distribution<int> pick(1, K);
                ll tested = 0;
                while (tested < per_set && (int)tris.size() < N) {
                    tested++;
                    int a = pick(rng), b = pick(rng), c = pick(rng);
                    if (a == b || b == c || a == c) continue;
                    ll da = doubled_area(P[a-1],P[b-1],P[c-1]);
                    if (da == 0 || (da & 1)) continue;
                    ll area = da >> 1;
                    if (area <= 1) continue;
                    if (!isPrime(area)) continue;
                    if (used_area.count(area)) continue;
                    used_area.insert(area);
                    tris.emplace_back(a,b,c);
                }
                rem -= min(rem, tested);

                // update best if needed
                if (tris.size() > best_count) {
                    best_count = tris.size();
                    bestP = P;
                    bestT = tris;
                }

                if ((int)tris.size() == N) {
                    ok = true;
                }
            }
        }

        if (ok) {
            cout << K << "\n";
            for (auto &p : bestP) cout << p.first << " " << p.second << "\n";
            for (auto &t : bestT) {
                int a,b,c; tie(a,b,c) = t;
                cout << a << " " << b << " " << c << "\n";
            }
        } else {
            // Fallback: print the best found pointset/triangles (may be incomplete)
            if (best_count > 0) {
                // print best pointset (K points)
                cout << K << "\n";
                for (auto &p : bestP) cout << p.first << " " << p.second << "\n";

                // print the triangles we found first
                for (auto &t : bestT) {
                    int a,b,c; tie(a,b,c) = t;
                    cout << a << " " << b << " " << c << "\n";
                }

                // fill remaining triangle lines with arbitrary distinct-index triples
                uniform_int_distribution<int> pick(1, K);
                int printed = (int)bestT.size();
                while (printed < N) {
                    int a = pick(rng), b = pick(rng), c = pick(rng);
                    int tries = 0;
                    while ((a==b || b==c || c==a) && tries++ < 50) {
                        a = pick(rng); b = pick(rng); c = pick(rng);
                    }
                    cout << a << " " << b << " " << c << "\n";
                    printed++;
                }
            } else {
                // If we never found any valid triangle in any pointset, fall back to random like before
                vector<pair<int,int>> P;
                P.reserve(K);
                unordered_set<u64> vis;
                vis.reserve(K*2);
                while ((int)P.size() < K) {
                    int x = coord(rng), y = coord(rng);
                    u64 key = ((u64)x << 32) ^ (u64)y;
                    if (vis.insert(key).second) P.push_back({x,y});
                }

                cout << K << "\n";
                for (auto &p : P) cout << p.first << " " << p.second << "\n";

                uniform_int_distribution<int> pick(1, K);
                for (int i = 0; i < N; i++) {
                    int a = pick(rng), b = pick(rng), c = pick(rng);
                    int tries = 0;
                    while ((a==b || b==c || c==a) && tries < 20) {
                        a = pick(rng); b = pick(rng); c = pick(rng);
                        tries++;
                    }
                    cout << a << " " << b << " " << c << "\n";
                }
            }
        }
    }
    return 0;
}