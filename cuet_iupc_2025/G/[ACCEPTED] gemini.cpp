#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 1000005;
const int LOGN = 21; // Enough for 10^6

// Global storage
vector<int> adj[MAXN];
int up[MAXN][LOGN];
int depth[MAXN];
int p[MAXN]; // The permutation
int B[MAXN]; // The array of LCAs of adjacent elements in p
long long D2[MAXN]; // Second order difference array
int L[MAXN], R[MAXN]; // For monotonic stack

// BFS to compute depths and 2^0 parents
void bfs_depth_parent(int root, int n) {
    // Reset used depth array entries
    for(int i = 1; i <= n; i++) depth[i] = 0;

    queue<int> q;
    q.push(root);
    depth[root] = 0;
    up[root][0] = root; 

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int v : adj[u]) {
            if(v != up[u][0]) { 
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                q.push(v);
            }
        }
    }
}

// Build Binary Lifting Table
void build_lca_table(int n) {
    for(int j = 1; j < LOGN; j++) {
        for(int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
}

// Get LCA in O(log N)
int get_lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    
    for(int j = LOGN - 1; j >= 0; j--) {
        if(depth[u] - (1 << j) >= depth[v]) {
            u = up[u][j];
        }
    }
    
    if(u == v) return u;
    
    for(int j = LOGN - 1; j >= 0; j--) {
        if(up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    // Reset adjacency list
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }

    // Base case n=1
    if (n == 1) {
        cout << p[0] << "\n";
        return;
    }

    // 1. LCA Preprocessing
    bfs_depth_parent(1, n);
    build_lca_table(n);

    // 2. Build B array (LCA of adjacent elements in p)
    int m = n - 1;
    for(int i = 0; i < m; i++) {
        B[i] = get_lca(p[i], p[i+1]);
    }

    // 3. Monotonic Stack for range of influence [L[i], R[i]]
    // We want the max range where B[i] has the minimum depth.
    vector<int> stack;
    
    // Right bound: Next Strictly Smaller Depth
    for(int i = 0; i < m; i++) {
        while(!stack.empty() && depth[B[stack.back()]] > depth[B[i]]) {
            R[stack.back()] = i;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    while(!stack.empty()) {
        R[stack.back()] = m;
        stack.pop_back();
    }

    // Left bound: Previous Smaller or Equal Depth
    for(int i = m - 1; i >= 0; i--) {
        while(!stack.empty() && depth[B[stack.back()]] >= depth[B[i]]) {
            L[stack.back()] = i;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    while(!stack.empty()) {
        L[stack.back()] = -1;
        stack.pop_back();
    }

    // 4. Difference Array Updates
    // Reset D2
    for(int i = 0; i <= n + 2; i++) D2[i] = 0;

    for(int i = 0; i < m; i++) {
        long long val = B[i];
        
        long long left_len = i - L[i];
        long long right_len = R[i] - i;
        
        if (left_len > right_len) swap(left_len, right_len);
        
        // Apply trapezoidal update to Second Order Difference Array
        D2[1] += val;
        D2[left_len + 1] -= val;
        D2[right_len + 1] -= val;
        // Fix: Use +1 here to correctly zero out the contribution after the range
        D2[left_len + right_len + 1] += val; 
    }

    // 5. Compute Final Answers
    // S0 is sum of p
    long long s0 = 0;
    for(int i = 0; i < n; i++) s0 += p[i];
    cout << s0;

    long long current_slope = 0;
    long long current_val = 0;
    
    // Calculate S1...Sn-1
    for(int k = 1; k < n; k++) {
        current_slope += D2[k];
        current_val += current_slope;
        cout << " " << current_val;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}