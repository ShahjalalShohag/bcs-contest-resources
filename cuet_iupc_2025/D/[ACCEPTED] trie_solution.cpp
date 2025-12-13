#include<bits/stdc++.h>
using namespace std;

// Alternative correct solution using Trie for minimum XOR pair
// O(n * 30) per test case

struct Trie {
    int ch[2];
    Trie() { ch[0] = ch[1] = -1; }
};

vector<Trie> trie;

void insert(int x) {
    int node = 0;
    for (int i = 29; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (trie[node].ch[bit] == -1) {
            trie[node].ch[bit] = trie.size();
            trie.push_back(Trie());
        }
        node = trie[node].ch[bit];
    }
}

int query(int x) {
    int node = 0;
    int res = 0;
    for (int i = 29; i >= 0; i--) {
        int bit = (x >> i) & 1;
        // Try to go same direction to minimize XOR
        if (trie[node].ch[bit] != -1) {
            node = trie[node].ch[bit];
        } else {
            res |= (1 << i);
            node = trie[node].ch[1 - bit];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        trie.clear();
        trie.push_back(Trie());
        
        int ans = INT_MAX;
        
        insert(a[0]);
        for (int i = 1; i < n; i++) {
            ans = min(ans, query(a[i]));
            insert(a[i]);
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
