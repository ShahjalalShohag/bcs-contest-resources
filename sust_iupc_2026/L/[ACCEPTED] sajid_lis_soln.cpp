// #pragma GCC optimize("O3,unroll-loops,Ofast")
// #pragma GCC target("avx2")
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define int long long
#define ll long long
#define endl '\n'

using namespace std;
using pii = pair<int, int>;
using tup = tuple<int, int, int>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define double long double

const int inf = 1e9;
const int mod = 998244353;
const double eps = 1e-16;
const int N = 300005;

void preprocess() {}

struct Node {
    int lis;
    Node *l, *r;
    Node() { lis = 0; l = r = NULL; }
    Node(int c) { lis = c; l = r = NULL; }
};

vector<Node> pool;

Node* newNode() {
    pool.emplace_back();
    return &pool.back();
}

void update(Node *node, int b, int e, int idx, int val) {
    if(e < idx or idx < b) return;
    if(b == e) { node->lis = max(node->lis, val); return; }

    int mid = b + e >> 1;

    if(idx <= mid) {
        if(!node->l) node->l = newNode();
        update(node->l, b, mid, idx, val);
    }
    
    else {
        if(!node->r) node->r = newNode();
        update(node->r, mid+1, e, idx, val);
    }

    if(node->l) node->lis = max(node->lis, node->l->lis);
    if(node->r) node->lis = max(node->lis, node->r->lis);
}

int query(Node *node, int b, int e, int l, int r) {
    if(!node or e < l or r < b) return 0;
    if(l <= b and e <= r) return node->lis;

    int mid = b + e >> 1;
    int lis = query(node->l, b, mid, l, r);
    lis = max(lis, query(node->r, mid+1, e, l, r));

    return lis;
}

int a[N];
const int MN = -1e9 - 1;
const int MX = 1e9 + 1;

ll add(ll l, ll r) {
    return r * (r + 1) / 2 - l * (l-1) / 2;
}

void solve(int tc) {
    int n, k;
    cin >> n >> k;

    for(int i=1; i<=n; i++) cin >> a[i];
    
    pool.clear();
    pool.reserve(35 * n + 5);

    ll sum = 0;
    Node* root = newNode();

    for(int i=1; i<=n; i++) {
        sum += a[i];
        ll now = query(root, MN, MX, MN, a[i]-1);
        update(root, MN, MX, a[i], now + 1);

        ll ans;
        if(root->lis < query(root, MN, MX, MN, root->lis-1) + 1) {
            ans = sum + add(root->lis, root->lis + k - 1);
        }
        else {
            ans = sum + 1ll * k * root->lis;
        }

        cout << ans << ' ';
    }

    cout << endl;
}

int32_t main() {
    cin.tie(NULL)->sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);

    preprocess();       

    int T = 1;  
    cin >> T;

    for (int i = 1; i <= T; i++) {
        solve(i);
    }

    return 0;
}