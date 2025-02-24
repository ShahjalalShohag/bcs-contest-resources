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

    int t;
    scanf("%d", &t);

    while(t--){
        int n;
        scanf("%d", &n);

        for(int i=n-1;i>n/2;i--) printf("%d ", i);
        for(int i=n/2-1;i>0;i--) printf("%d ", i);
        if(n>=2) printf("%d ", n/2);
        printf("%d\n", n);
    }

    return 0;
}