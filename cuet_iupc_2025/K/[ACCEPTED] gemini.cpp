#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Standard modular arithmetic
long long power(long long base, long long exp) {
    long long res = 1;
    base %= 998244353;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % 998244353;
        base = (base * base) % 998244353;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, 998244353 - 2);
}

const int MAXN = 1000005;
const int MOD = 998244353;
long long fact[MAXN], invFact[MAXN];
long long inv[MAXN]; // Inverses of numbers 1 to MAXN

// Precompute factorials and modular inverses
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
    }
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAXN - 1] = modInverse(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Global variables for graph and DP
vector<int> adj[MAXN];
int sz[MAXN];
long long C[MAXN]; // Stores C_u for each node
int parent_node[MAXN];

// First DFS: Compute subtree sizes rooted at 1
// Implemented iteratively to prevent stack overflow on deep trees
void dfs_sz(int root, int n) {
    vector<int> order;
    vector<int> stk = {root};
    parent_node[root] = 0;
    
    while(!stk.empty()){
        int u = stk.back();
        stk.pop_back();
        order.push_back(u);
        for(int v : adj[u]){
            if(v != parent_node[u]){
                parent_node[v] = u;
                stk.push_back(v);
            }
        }
    }
    
    // Process in reverse topological order (bottom-up)
    for(int i = n-1; i >= 0; i--){
        int u = order[i];
        sz[u] = 1;
        for(int v : adj[u]){
            if(v != parent_node[u]){
                sz[u] += sz[v];
            }
        }
    }
}

// Second DFS: Re-rooting technique to compute C[u] for all u
void dfs_reroot(int root, int n) {
    // Top-down Order using stack
    vector<int> stk = {root};
    while(!stk.empty()){
        int u = stk.back();
        stk.pop_back();
        
        for(int v : adj[u]){
            if(v != parent_node[u]){
                // Transition formula when moving root from u to neighbor v:
                // C[v] = C[u] * sz[v] * inv[n - sz[v]]
                // Here sz[v] is size in 1-rooted tree, (n - sz[v]) is the size of the 
                // component containing u when edge (u,v) is cut.
                long long term = (C[u] * sz[v]) % MOD;
                term = (term * inv[n - sz[v]]) % MOD;
                C[v] = term;
                stk.push_back(v);
            }
        }
    }
}

void solve() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return;
    
    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // We need at least n-1 distinct weights
    if (k < n - 1) {
        cout << 0 << "\n";
        return;
    }

    // 1. Compute sizes rooted at 1
    dfs_sz(1, n);

    // 2. Compute C[1] (Base case for rerooting)
    // C[1] = (n-1)! * product(1/sz[v] for all v != 1)
    long long prod_sz_inv = 1;
    for(int i = 2; i <= n; i++){
        prod_sz_inv = (prod_sz_inv * inv[sz[i]]) % MOD;
    }
    C[1] = (fact[n - 1] * prod_sz_inv) % MOD;

    // 3. Compute all C[u] via rerooting DP
    dfs_reroot(1, n);

    // 4. Calculate Inclusion-Exclusion Sum
    // W = Sum(C_u) - Sum(C_{uv})
    long long sum_C_nodes = 0;
    for(int i = 1; i <= n; i++){
        sum_C_nodes = (sum_C_nodes + C[i]) % MOD;
    }

    long long sum_C_edges = 0;
    long long inv_n_minus_1 = inv[n - 1];
    
    // Iterate over all edges (u, v). We use the parent pointers from DFS.
    for(int v = 2; v <= n; v++){
        int u = parent_node[v];
        // Formula: C_{uv} = C_u * sz[v] / (n-1)
        long long term = (C[u] * sz[v]) % MOD;
        term = (term * inv_n_minus_1) % MOD;
        sum_C_edges = (sum_C_edges + term) % MOD;
    }

    long long W = (sum_C_nodes - sum_C_edges + MOD) % MOD;
    
    // 5. Compute binom(k+1, n) manually since k is large
    // binom(N, K) = N * (N-1) * ... * (N-K+1) / K!
    // Here N = k+1, K = n
    long long num = 1;
    for(int i = 0; i < n; i++){
        long long term = (k + 1 - i) % MOD;
        num = (num * term) % MOD;
    }
    long long binom_val = (num * invFact[n]) % MOD;

    // Final Answer
    cout << (W * binom_val) % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}