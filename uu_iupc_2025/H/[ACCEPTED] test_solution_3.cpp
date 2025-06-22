#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define pb push_back

pair<pair<int,int>,int> a[2000007];
void redix_sort(int len){
    int cnt[len];
    pair<pair<int,int>,int> temp[len];
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<len;i++)
        cnt[a[i].first.second]++;
    for(int i=1;i<len;i++)
        cnt[i]+=cnt[i-1];
    for(int i=len-1;i>=0;i--){
        cnt[a[i].first.second]--;
        temp[cnt[a[i].first.second]]=a[i];
    }

    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<len;i++)
        cnt[temp[i].first.first]++;
    for(int i=1;i<len;i++)
        cnt[i]+=cnt[i-1];
    for(int i=len-1;i>=0;i--){
        cnt[temp[i].first.first]--;
        a[cnt[temp[i].first.first]]=temp[i];
    }
}

vector<int> suffix_array(string const& s) {
    int len = s.size();
    int pos[len];

    vector<pair<int,int>> temp;
    for(int i=0;i<len;i++)
        temp.pb({(int)s[i],i});
    sort(temp.begin(),temp.end());
    pos[temp[0].second]=0;
    for(int i=1,ok=0;i<len;i++){
        if(temp[i].first!=temp[i-1].first) ok++;
        pos[temp[i].second]=ok;
    }

    vector<int> ans(len, 0);
    for(int k=1;k<=len;){
        k*=2;
        for(int i=0;i<len;i++)
            a[i]={{pos[i],pos[(i+k/2)%len]},i};
        redix_sort(len);
        pos[a[0].second]=0;
        ans[0]=a[0].second;
        for(int i=1,ok=0;i<len;i++){
            if(a[i].first!=a[i-1].first) ok++;
            pos[a[i].second]=ok;
            ans[i]=a[i].second;
        }
    }
    return ans;
}
    

vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]+1] = k;
        if (k)
            k--;
    }
    return lcp;
}

int lg[1000001];
int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    int pw[22];
    pw[0]=1;
    for(int i=1;i<22;i++) pw[i]=pw[i-1]*2;

    for(int i=1,v=-1,j=0;i<=1000000;i++){
        if(i==pw[j]){
            v++;
            j++;
        }
        lg[i]=v;
    }

    int t;
    cin>>t;

    while(t--){
        int n,m,q;
        cin>>n>>m>>q;
        string p,b,s;
        cin>>p>>b;
        s=p+"$"+b+"#";
    
        int len=s.size();

        vector<int> sa = suffix_array(s);
        vector<int> lcp = lcp_construction(s, sa);

        // cout<<s<<" "<<sa.size()<<endl;
        // for(int i=0;i<len;i++) cout<<i<<" "<<sa[i]<<" "<<lcp[i]<<endl;
        
        int ran[m];
        memset(ran, 0, sizeof(ran));
        for(int i=1,mn=0;i<len;i++){
            if(sa[i]<n) continue;
            if(sa[i-1]<n) mn=lcp[i];
            mn=min(mn, lcp[i]);
            ran[sa[i]-n-1]=max(ran[sa[i]-n-1],mn);
        }
        for(int i=len-2,mn=0;i>=0;i--){
            if(sa[i]<n) continue;
            if(sa[i+1]<n) mn=lcp[i+1];
            ran[sa[i]-n-1]=max(ran[sa[i]-n-1],mn);
            mn=min(mn, lcp[i]);
        }

        vector<int>sp[m];
        for(int i=1;i<=m;i*=2){
            for(int j=0;j<m;j++){
                if(i==1){
                    sp[j].resize(lg[m-j]+1);
                    sp[j][0]=(ran[j]);
                    continue;
                }
                if(j+i-1>=m) break;
                sp[j][lg[i]]=(min(sp[j][lg[i/2]], sp[j+i/2][lg[i/2]]));
            }
        }

        while(q--){
            int l,r,out=0;
            cin>>l>>r;
            l--,r--;
            int lf=1, rt=r-l+1;
            while(lf<=rt){
                int md=(lf+rt)/2;
                int lff=l;
                int rtt=r-md+1;
                int rng = pw[lg[rtt-lff+1]];
                int mn=min(sp[lff][lg[rtt-lff+1]],sp[rtt-rng+1][lg[rtt-lff+1]]);
                if(mn>=md){
                    out=md;
                    lf=md+1;
                }
                else rt=md-1;
            }
            cout<<out<<endl;
        }
    }
	return 0;
}