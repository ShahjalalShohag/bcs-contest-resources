#include<bits/stdc++.h>
using namespace std;

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define LL long long
#define asort(ar,n) sort(ar,ar+n)

int main()
{
    FastIO;

    LL t=1,n; cin>>t;
    while(t--)
    {
        cin>>n;

        LL arr[n];
        for(LL i=0; i<n; i++)
        {
            cin>>arr[i];
        }
        asort(arr,n);

        LL ans=n;
        LL start=0;
        for(LL i=1; i<n; i++)
        {
            if(arr[i]-arr[i-1]>1)
            {
                ans=min(ans,start+(n-i));
                start=i;
            }
        }
        ans=min(ans,start);

        cout<<ans<<"\n";
    }

    return 0;
}
