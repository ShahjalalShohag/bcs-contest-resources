#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 1000005

int n, arr[mxn];

int main()
{
    fastio;
    
    int t, tc=1;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n; i++) cin>>arr[i];
        ll ans = 0;
        stack<vector<ll>>st;
        st.push({n+2,-1,-1});
        arr[n+2]=n+2;

        for(int i=n-1; i>=0; i--){
            while(arr[i]>=arr[st.top()[0]]){
                st.pop();
            }
            vector<ll>now = {i,i,1};
            if(arr[i]+1==arr[st.top()[0]]){
                now[1]+=st.top()[1];
                now[2]+=st.top()[2];
            }
            st.push(now);
            if(arr[i]==0){
                vector<ll>top = st.top();
                ans+=top[2]*n-top[1];
            }
        }

        cout<<ans<<"\n";
    }

    return 0;
}