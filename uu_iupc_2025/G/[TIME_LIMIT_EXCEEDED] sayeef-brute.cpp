#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 1000005

int vis[mxn];

int main()
{
    fastio;
    
    int t, tc=1;
    cin>>t;
    while(t--){
        int n;
        cin>>n;

        int arr[n];
        for(int i=0; i<n; i++) cin>>arr[i];

        ll ans=0;

        for(int i=0; i<n+3; i++) vis[i]=0;

        for(int i=0; i<n; i++){
            int mex=0, mx=0;
            for(int j=i; j<n; j++){
                mx=max(mx,arr[j]);
                vis[mx]=i+1;
                while(vis[mex]==i+1) mex++;
                ans+=mex;
            }
        }

        cout<<ans<<"\n";
    }

    return 0;
}