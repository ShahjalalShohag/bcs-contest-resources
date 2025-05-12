#include <bits/stdc++.h>
using namespace std;

// Pure brute‐force via BFS on the bitmask of node values.
// Note: this will only finish for very small n (n ≤ ~20).

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<pair<int,int>> edges(n-1);
        for(int i = 0; i < n-1; i++){
            cin >> edges[i].first >> edges[i].second;
            --edges[i].first;
            --edges[i].second;
        }

        // If n is too large, bail out (pure brute won't handle it).
        if(n > 20){
            cout << "-1\n";
            continue;
        }

        // initial mask
        int start = 0;
        for(int i = 0; i < n; i++){
            if(a[i]) start |= (1<<i);
        }
        int target = 0;

        // precompute flip‐masks for each edge
        vector<int> flipMask(n-1);
        for(int i = 0; i < n-1; i++){
            int u = edges[i].first;
            int v = edges[i].second;
            flipMask[i] = (1<<u) | (1<<v);
        }

        // BFS
        unordered_map<int,int> dist;
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        int answer = -1;
        while(!q.empty()){
            int mask = q.front(); q.pop();
            int d = dist[mask];
            if(mask == target){
                answer = d;
                break;
            }
            // try every edge flip
            for(int i = 0; i < n-1; i++){
                int nm = mask ^ flipMask[i];
                if(!dist.count(nm)){
                    dist[nm] = d + 1;
                    q.push(nm);
                }
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
