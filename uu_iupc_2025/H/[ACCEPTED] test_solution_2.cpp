#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define pb push_back

vector<int> suffix_array(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
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