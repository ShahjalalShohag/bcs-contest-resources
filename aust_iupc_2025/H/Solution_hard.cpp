#include <bits/stdc++.h>
using namespace std;

template <typename T>
using min_heap=priority_queue<T, vector<T>, greater<T>>;

int nodeMap[3000001], dis[2000000];
vector<pair<int, int>> g[2000000];

void build(int u, int l, int r, bool isOdd){
    if(l==r){
        if(isOdd) nodeMap[2*l-1] = u;
        else nodeMap[2*(l-1)] = u;
        return;
    }

    build(2*u, l, (l+r)/2, isOdd);
    build(2*u+1, (l+r)/2+1, r, isOdd);
    g[2*u].push_back({u, 0});
    g[2*u+1].push_back({u, 0});
}

void addEdge(int u, int l, int r, int i, int j, int v){
    if(l>j || r<i) return;
    if(l>=i && r<=j){
        g[u].push_back({v, 1});
        return;
    }
    addEdge(2*u, l, (l+r)/2, i, j, v);
    addEdge(2*u+1, (l+r)/2+1, r, i, j, v);
}

int main()
{
    int T;
    cin>>T;

    while(T--){
        int n,k;
        cin>>n>>k;

        for(int i=0;i<=4*n;i++){
            g[i].clear();
            dis[i]=INT_MAX;
        }

        g[2].push_back({1, 0});
        g[3].push_back({1, 0});
        build(2, 1, n/2+1, false);
        build(3, 1, (n+1)/2, true);
        for(int numberOfOnes=1; numberOfOnes<=n; numberOfOnes++){
            int numberOfZeros = n - numberOfOnes;
            int l, r;

            if(numberOfZeros >= n - k) l = numberOfZeros - (n - k);
            else l = n - k - numberOfZeros;

            if(numberOfOnes >= n - k) r = numberOfZeros + n - k;
            else r = numberOfZeros - (n - k - numberOfOnes) + numberOfOnes;

            if(r<l) continue;
            if(l%2) addEdge(3, 1, (n+1)/2, (l+1)/2, (r+1)/2, nodeMap[numberOfOnes]);
            else addEdge(2, 1, n/2+1, l/2+1, r/2+1, nodeMap[numberOfOnes]);
        }

        min_heap<pair<int, int>> pq;
        pq.push({0, nodeMap[0]});
        dis[nodeMap[0]] = 0;

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for(int i=0; i<g[u].size(); i++){
                int v=g[u][i].first;
                int w=g[u][i].second;
                if(dis[v] <= dis[u] + w) continue;
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }

        for(int i=1; i<=n; i++){
            if(dis[nodeMap[i]] == INT_MAX) dis[nodeMap[i]] = -1;
            cout<<dis[nodeMap[i]];
            if(i!=n) cout<<" ";
            else cout<<endl;
        }
    }

    return 0;
}