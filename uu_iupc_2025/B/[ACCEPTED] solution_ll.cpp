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

ll lowestPrimeFactor[5000001], color[500001], mod = 998244353, numberOfPrimes;
vector<ll> graph[500001];

bool dfs(ll u){
    for(ll i = 0; i < graph[u].size(); i++){
        ll v = graph[u][i];
        if(color[v] != -1){
            if(color[u] == color[v]) return false;
            continue;
        }
        color[v] = (color[u] == 0);
        ll res = dfs(v);
        if(!res) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(ll i = 2; i <= 5000000; i++){
        if(lowestPrimeFactor[i]) continue;
        numberOfPrimes++;
        for(ll j = i; j <= 5000000; j += i){
            if(lowestPrimeFactor[j]) continue;
            lowestPrimeFactor[j] = i;
        }
    }

    ll t;
    cin>>t;

    while(t--){
        ll n;
        bool doesAnswerExist = true;
        vector<pair<ll, ll>> primeFactors;
        cin>>n;

        for(ll i = 0; i < n; i++){
            graph[i].clear();
            color[i] = -1;
            ll lastPrime = -1, inp;
            cin>>inp;
            if(primeFactors.size() > 2 * numberOfPrimes) continue;
            while(inp != 1){
                if(lastPrime != lowestPrimeFactor[inp]){
                    primeFactors.pb({lowestPrimeFactor[inp], i});
                    lastPrime = lowestPrimeFactor[inp];
                }
                inp /= lowestPrimeFactor[inp];
            }
        }

        sort(all(primeFactors));
        for(ll i = 2; i < primeFactors.size(); i++){
            if(primeFactors[i].first == primeFactors[i - 1].first && 
                primeFactors[i].first == primeFactors[i - 2].first){
                    doesAnswerExist = false;
                    break;
                }
        }

        for(ll i = 1; i < primeFactors.size(); i++){
            if(primeFactors[i].first == primeFactors[i - 1].first){
                graph[primeFactors[i].second].pb(primeFactors[i - 1].second);
                graph[primeFactors[i - 1].second].pb(primeFactors[i].second);

            }
        }

        ll ans = 1, numberOfOneLenComp = 0;
        for(ll i = 0; i < n; i++){
            if(color[i] != -1) continue;
            bool ret = dfs(i);
            if(ret == false){
                doesAnswerExist = false;
                break;
            }
            ans = (ans * 2) % mod;
            if(graph[i].empty()) numberOfOneLenComp++;
        }

        if(numberOfOneLenComp == n) ans = (ans + mod - 2) % mod;

        if(doesAnswerExist) cout<<ans<<endl;
        else cout<<0<<endl;
    }

    return 0;
}