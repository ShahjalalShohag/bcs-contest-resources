// Correct but Tricky TLE Solution
// Builds full cliques for each prime factor, then checks bipartiteness
// Very slow when a common prime divides many items.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 5000005;
const int MOD = 998244353;

int addmod(int a, int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int submod(int a, int b){ a-=b; if(a<0) a+=MOD; return a; }
ll modexp(ll a, ll e) {
    ll res = 1;
    while(e>0) {
        if(e&1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int lpf[MAXA];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute least-prime factors up to MAXA
    for(int i = 2; i < MAXA; i++){
        if(lpf[i] == 0){
            for(ll j = i; j < MAXA; j += i) 
                if(lpf[j] == 0) lpf[j] = i;
        }
    }

    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];

        // Map each prime to list of item indices
        unordered_map<int, vector<int>> pd;
        pd.reserve(n * 2);
        pd.max_load_factor(0.7f);

        // Factor each a[i]
        for(int i = 0; i < n; i++){
            int x = a[i];
            vector<int> primes;
            while(x > 1){
                int p = lpf[x];
                primes.push_back(p);
                while(x % p == 0) x /= p;
            }
            // record
            for(int p: primes){
                pd[p].push_back(i);
            }
        }

        // Build full adjacency (cliques) per prime
        vector<vector<int>> adj(n);
        ll totalEdges = 0;
        for(auto &kv: pd){
            auto &vec = kv.second;
            int k = vec.size();
            // connect every pair in vec
            for(int i = 0; i < k; i++){
                for(int j = i+1; j < k; j++){
                    int u = vec[i], v = vec[j];
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                    totalEdges++;
                }
            }
        }

        // Check bipartiteness and count components
        vector<int> color(n, -1);
        bool ok = true;
        int comps = 0;
        for(int i = 0; i < n && ok; i++){
            if(color[i] != -1) continue;
            comps++;
            queue<int> q;
            color[i] = 0;
            q.push(i);
            while(!q.empty() && ok){
                int u = q.front(); q.pop();
                for(int v: adj[u]){
                    if(color[v] == -1){
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if(color[v] == color[u]){
                        ok = false;
                        break;
                    }
                }
            }
        }

        if(!ok){
            cout << 0 << '\n';
            continue;
        }

        // Compute answer
        ll ans;
        if(totalEdges == 0){
            // no constraints => subtract the two empty-group splits
            ans = submod((int)modexp(2, n), 2);
        } else {
            // each component gives 2 colorings
            ans = modexp(2, comps);
        }
        cout << ans << '\n';
    }
    return 0;
}
