#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define all(x) x.begin(),x.end()
#define Max 10000000000000000

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using min_heap=priority_queue<T, vector<T>, greater<T>>;

int color[500001];
ll mod = 998244353;
vector<int> graph[500001];
pair<int, int> cnt[5000001];

bool dfs(int u){
    for(int i = 0; i < graph[u].size(); i++){
        int v = graph[u][i];
        if(color[v] != -1){
            if(color[u] == color[v]) return false;
            continue;
        }
        color[v] = (color[u] == 0);
        bool res = dfs(v);
        if(!res) return false;
    }
    return true;
}

int main()
{
    int t;
    scanf("%d", &t);

    read:
    while(t--){
        int n;
        bool doesAnswerExist = true;
        vector<pair<int, int>> primeFactors;
        vector<int> inp_arr;
        scanf("%d", &n);

        for(int i = 0; i < n; i++){
            graph[i].clear();
            color[i] = -1;
            int x;
            scanf("%d", &x);
            inp_arr.push_back(x);
        }

        for(int i = 0; i < inp_arr.size(); i++){
            int inp = inp_arr[i];
            for(int j = 2; j * j <= inp; j++){
                if(inp % j) continue;
                if(cnt[j].first != t + 1) cnt[j] = {t + 1, 0};
                cnt[j].second++;
                if(cnt[j].second > 2){
                    printf("0\n");
                    goto read;
                }
                primeFactors.push_back({j, i});
                while(inp % j == 0) inp /= j;
            }
            if(inp != 1){
                if(cnt[inp].first != t + 1) cnt[inp] = {t + 1, 0};
                cnt[inp].second++;
                if(cnt[inp].second > 2){
                    printf("0\n");
                    goto read;
                }
                primeFactors.push_back({inp, i});
            }
        }

        sort(all(primeFactors));
        for(int i = 2; i < primeFactors.size(); i++){
            if(primeFactors[i].first == primeFactors[i - 1].first && 
                primeFactors[i].first == primeFactors[i - 2].first){
                    doesAnswerExist = false;
                    break;
                }
        }

        for(int i = 1; i < primeFactors.size(); i++){
            if(primeFactors[i].first == primeFactors[i - 1].first){
                graph[primeFactors[i].second].pb(primeFactors[i - 1].second);
                graph[primeFactors[i - 1].second].pb(primeFactors[i].second);

            }
        }

        ll ans = 1;
        int numberOfOneLenComp = 0;
        for(int i = 0; i < n; i++){
            if(color[i] != -1) continue;
            bool ret = dfs(i);
            if(ret == false){
                doesAnswerExist = false;
                break;
            }
            ans = (ans * 2LL) % mod;
            if(graph[i].empty()) numberOfOneLenComp++;
        }

        if(numberOfOneLenComp == n) ans = (ans + mod - 2) % mod;

        if(!doesAnswerExist) ans = 0;
        printf("%lli\n", ans);
    }

    return 0;
}