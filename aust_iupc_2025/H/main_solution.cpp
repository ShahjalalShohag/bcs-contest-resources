#include <bits/stdc++.h>
using namespace std;

int main()
{

    int T;
    cin>>T;

    while(T--){
        int n, k;
        cin>>n>>k;

        set<int> oddNodes, evenNodes;
        for(int i=1;i<=n;i++){
            if(i%2) oddNodes.insert(i);
            else evenNodes.insert(i);
        }

        int dis[n+1];
        memset(dis, -1, sizeof(dis));
        queue<int> q;
        q.push(0);
        dis[0]=0;

        while(!q.empty()){
            int numberOfOnes = q.front();
            q.pop();
            int numberOfZeros = n - numberOfOnes;

            int l, r;
            if(numberOfZeros >= n - k) l = numberOfZeros - (n - k);
            else l = n - k - numberOfZeros;

            if(numberOfOnes >= n - k) r = numberOfZeros + n - k;
            else r = numberOfOnes + numberOfZeros - (n - k - numberOfOnes);

            if(l%2) {
                auto it = oddNodes.lower_bound(l);
                vector<int> deletableNodes;
                while(it != oddNodes.end() && *it <= r){
                    dis[*it]=dis[numberOfOnes] + 1;
                    q.push(*it);
                    deletableNodes.push_back(*it);
                    it++;
                }
                for(int i = 0; i < deletableNodes.size(); i++) oddNodes.erase(deletableNodes[i]);
            }
            else {
                auto it = evenNodes.lower_bound(l);
                vector<int> deletableNodes;
                while(it != evenNodes.end() && *it <= r){
                    dis[*it]=dis[numberOfOnes] + 1;
                    q.push(*it);
                    deletableNodes.push_back(*it);
                    it++;
                }
                for(int i = 0; i < deletableNodes.size(); i++) evenNodes.erase(deletableNodes[i]);
            }
        }

        for(int i = 1; i <= n; i++) cout<<dis[i]<<" ";
        cout<<endl;
    }

    return 0;
}