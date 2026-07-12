#include<bits/stdc++.h>
using namespace std;

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define LL int

const LL MXX=3e5+3;
const LL inf=1e9;

set<pair<LL,LL>>adb[MXX];
set<pair<LL,LL>>adw[MXX];
LL clr[MXX];
LL par[MXX];
bool vis[MXX];
vector<LL>ans;
LL start;

bool dfs1(LL v)
{
    clr[v]=1;
    for(pair<LL,LL> w: adb[v])
    {
        LL u=w.first;
        if(clr[u]==0)
        {
            par[u]=v;
            if(dfs1(u)) return true;
        }
        else if(clr[u]==1)
        {
            start=u;
            return true;
        }
    }

    clr[v]=2;
    return false;
}

bool isCyclic(LL n) {
    start=-1;

    for(LL v=0; v<n; v++)
        if(clr[v]==0 and dfs1(v))
            break;

    if(start==-1) return false;
    return true;
}

void dfs2(LL v)
{
    vis[v]=true;
    for(pair<LL,LL> w: adb[v])
    {
        LL u=w.first;
        if(!vis[u]) dfs2(u);
    }

    ans.push_back(v);
}

bool topoSort(LL n) {
    ans.clear();
    dfs2(1);
    reverse(ans.begin(), ans.end());
    return vis[n];
}

int main()
{
    FastIO;

    LL t=1,n,m,u,v,c; cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(LL i=1; i<=n; i++)
        {
            adb[i].clear();
            adw[i].clear();
            clr[i]=0;
            par[i]=-1;
            vis[i]=false;
        }

        bool isSrcOrDstInv=false;
        vector<pair<LL,pair<LL,LL>>>edg;
        for(LL i=0; i<m; i++)
        {
            cin>>u>>v>>c;

            if(c) adb[u].insert({v,i});
            else adw[u].insert({v,i});

            edg.push_back({u,{v,c}});

            if(c and (v==1 or u==n)) isSrcOrDstInv=true;
        }

        if(isSrcOrDstInv or isCyclic(n) or !topoSort(n)) cout<<"-1\n";
        else
        {
            LL pos[n+1]={};
            bool idg[n+1]={};
            bool odg[n+1]={};
            LL syz=ans.size();
            for(LL i=0; i<syz; i++) pos[ans[i]]=i+1;

            bool flag=false;
            vector<LL>wgts;
            for(LL i=0; i<m; i++)
            {
                u=edg[i].first;
                v=edg[i].second.first;
                c=edg[i].second.second;

                LL wgt=inf;
                if(c)
                {
                    if(pos[v]==0 or pos[u]==0)
                    {
                        flag=true;
                        break;
                    }

                    wgt=pos[v]-pos[u];

                    odg[u]=true;
                    idg[v]=true;
                }

                wgts.push_back(wgt);
            }

            for(auto it:ans)
            {
                if(it==1 and odg[it] and !idg[it]) continue;
                else if(it==n and !odg[it] and idg[it]) continue;
                else if(odg[it] and idg[it]) continue;
                else flag=true;
            }

            if(flag) cout<<"-1\n";
            else
            {
                for(auto it: wgts) cout<<it<<" ";
                cout<<"\n";
            }
        }
    }

    return 0;
}