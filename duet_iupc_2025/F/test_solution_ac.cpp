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

int main()
{

    ll t;
    cin>>t;

    while(t--){
        ll n,m;
        cin>>n>>m;
        ll dis;
        ll a[n][m];
        if(n>m){
            if(n-m>m) dis = 2*m;
            else dis=n;
            for(ll j=0;j<m;j++){
                ll x=n-j;
                for(ll i=0;i<n;i++){
                    if(x){
                        a[i][j]=x;
                        x--;
                    }
                    else a[i][j]=1;
                }
            }
        }
        else{
            if(m-n>n) dis=2*n;
            else dis=m;
            for(ll i=0;i<n;i++){
                ll x=m-i;
                for(ll j=0;j<m;j++){
                    if(x){
                        a[i][j]=x;
                        x--;
                    }
                    else a[i][j]=1;
                }
            }
        }
        cout<<dis<<endl;
        for(ll i=0;i<n;i++){
            for(ll j=0;j<m;j++) cout<<a[i][j]<<" ";
            cout<<endl;
        }
    }

    return 0;
}

/*
1 2 3
1 1 2
*/