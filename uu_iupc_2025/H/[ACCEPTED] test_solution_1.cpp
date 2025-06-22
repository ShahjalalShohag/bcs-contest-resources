#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define pb push_back

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) {
        if (c + 1 < val_range) ++l[c + 1];
        ++r[c];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA)
        if (i >= 1 && sl[i - 1]) {
            SA[l[vec[i - 1]]++] = i - 1;
        }
    fill(r.begin(), r.end(), 0);
    for (int c : vec)
        ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
        if (i >= 1 && !sl[i - 1]) {
            SA[--r[vec[i - 1]]] = i - 1;
        }
}
   
vector<int> SA_IS(const vector<int> &vec, int val_range) {
    const int n = vec.size();
    vector<int> SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i)
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
            new_lms_idx[k++] = SA[i];
        }
    int cur = 0;
    SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) {
            SA[j] = ++cur;
            continue;
        }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) {
                flag = true;
                break;
            }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i)
        lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) {
            new_lms_idx[i] = lms_idx[lms_SA[i]];
        }
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}
vector<int> suffix_array(const string &s, const int LIM = 128) {
    vector<int> vec(s.size() + 1);
    copy(begin(s), end(s), begin(vec));
    vec.back() = '!';
    auto ret = SA_IS(vec, LIM);
    ret.erase(ret.begin());
    return ret;
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