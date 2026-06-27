#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()
#define Max 10000000000000000
#define min_heap priority_queue <ll, vector<ll>, greater<ll> >

template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef unsigned long long ull;
const ull root=1000000000000000003ULL;

char str[300007],flip[300007];
ull hsh[300007],hshR[300007],pw[300007];
ll dOpen[300009],dClose[300009];
ll opensq[300007],closesq[300007];

pair<pair<ll,ll>,ll> run[300007];
ll rc;

ll sa_len[600007],sa_link[600007],sa_cnt[600007];
ll sa_go[600007][26];
ll sa_sz,sa_last;

void hashify(ull* h,char* s,ll n){
    h[0]=0;
    for(ll i=0;i<n;i++)
        h[i+1]=h[i]*root+(ull)s[i];
}

ull cut(ull* h,ll l,ll len){
    return h[l+len]-h[l]*pw[len];
}

ll matchFront(ull* h,ll i,ll j,ll n){
    if(i==j) return n-i;
    ll lo=0,hi=n-(i>j?i:j);
    while(lo<hi){
        ll mid=lo+hi+1>>1;
        if(cut(h,i,mid)==cut(h,j,mid)) lo=mid;
        else hi=mid-1;
    }
    return lo;
}

void sam_reset(){
    sa_len[0]=0;
    sa_link[0]=-1;
    for(ll c=0;c<26;c++) sa_go[0][c]=-1;
    sa_cnt[0]=0;
    sa_sz=1;
    sa_last=0;
}

void sam_add(ll c){
    ll cur=sa_sz++;
    sa_len[cur]=sa_len[sa_last]+1;
    sa_cnt[cur]=1;
    for(ll i=0;i<26;i++) sa_go[cur][i]=-1;
    ll p=sa_last;
    while(p!=-1&&sa_go[p][c]==-1){
        sa_go[p][c]=cur;
        p=sa_link[p];
    }
    if(p==-1) sa_link[cur]=0;
    else{
        ll q=sa_go[p][c];
        if(sa_len[p]+1==sa_len[q]) sa_link[cur]=q;
        else{
            ll cl=sa_sz++;
            sa_len[cl]=sa_len[p]+1;
            sa_link[cl]=sa_link[q];
            for(ll i=0;i<26;i++) sa_go[cl][i]=sa_go[q][i];
            sa_cnt[cl]=0;
            while(p!=-1&&sa_go[p][c]==q){
                sa_go[p][c]=cl;
                p=sa_link[p];
            }
            sa_link[q]=cl;
            sa_link[cur]=cl;
        }
    }
    sa_last=cur;
}

ll equalPairs(char* s,ll n){
    sam_reset();
    for(ll i=0;i<n;i++) sam_add(s[i]-'a');
    vector<ll> ord(sa_sz),bkt(n+1,0);
    for(ll v=1;v<sa_sz;v++) bkt[sa_len[v]]++;
    for(ll i=1;i<=n;i++) bkt[i]+=bkt[i-1];
    for(ll v=1;v<sa_sz;v++) ord[--bkt[sa_len[v]]]=v;
    for(ll k=sa_sz-2;k>=0;k--) sa_cnt[sa_link[ord[k]]]+=sa_cnt[ord[k]];
    ll tot=0;
    for(ll v=1;v<sa_sz;v++){
        ll c=sa_cnt[v];
        tot+=c*(c-1)/2*(sa_len[v]-sa_len[sa_link[v]]);
    }
    return tot;
}

void carve(ll n){
    map<pair<ll,ll>,ll> seg;
    for(ll p=1;p+p<=n;p++)
        for(ll i=0;i+p<n;i+=p){
            ll j=i+p;
            ll right=matchFront(hsh,i,j,n);
            ll left=i?matchFront(hshR,n-i,n-j,n):0;
            if(left+right<p) continue;
            ll lo=i-left,hi=j+right-1;
            if(hi-lo+1<p+p) continue;
            pair<ll,ll> who=mp(lo,hi);
            auto it=seg.find(who);
            if(it==seg.end()||p<it->second) seg[who]=p;
        }
    rc=0;
    for(auto& e:seg) run[rc++]=mp(e.first,e.second);
}

int main()
{
    ll t;
    cin>>t;

    pw[0]=1;
    for(ll i=1;i<300007;i++)
        pw[i]=pw[i-1]*root;

    while(t--){
        scanf("%s",str);
        ll n=strlen(str);
        if(n<=1){
            printf("0\n");
            continue;
        }

        for(ll i=0;i<n;i++) flip[i]=str[n-1-i];
        hashify(hsh,str,n);
        hashify(hshR,flip,n);

        carve(n);

        for(ll i=0;i<=n+1;i++) dOpen[i]=dClose[i]=0;
        ll overlap=0;
        for(ll r=0;r<rc;r++){
            ll lo=run[r].first.first,hi=run[r].first.second,p=run[r].second;
            ll wide=hi-lo+1;
            for(ll d=p;d<wide;d+=p){
                ll edge=hi+1-2*d;
                if(edge<lo) break;
                ll cnt=edge-lo+1;
                overlap+=edge*cnt-(lo+edge)*cnt/2;
            }
            for(ll h=p;2*h<=wide;h+=p){
                dOpen[lo]++;
                dOpen[hi-2*h+2]--;
                dClose[lo+2*h-1]++;
                dClose[hi+1]--;
            }
        }

        ll a=0,b=0;
        for(ll i=0;i<n;i++){
            a+=dOpen[i];
            opensq[i]=a;
            b+=dClose[i];
            closesq[i]=b;
        }

        ll cross=0;
        for(ll c=1;c<n;c++)
            cross+=closesq[c-1]*opensq[c];

        ll twin=equalPairs(str,n);

        printf("%lld\n",2*(twin-overlap)+cross);
    }

	return 0;
}
