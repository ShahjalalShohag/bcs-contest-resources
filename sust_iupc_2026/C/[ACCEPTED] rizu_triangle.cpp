#include<bits/stdc++.h>
using namespace std;

#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define LL long long
#define vsort(vc) sort(vc.begin(),vc.end())

struct PT
{
    LL x, y;
    PT() {}
    PT(LL x, LL y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    bool operator < (const PT &p) const
    {
        return ((x < p.x) or ((x == p.x) and (y < p.y)));
    }
};

LL signedArea(PT a, PT b, PT c)
{
    PT p[3]= {a,b,c};
    LL area = 0;
    for(LL i = 0; i < 3; i++)
    {
        LL j = (i+1) % 3;
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area;
}

bool isInside(PT a, PT b, PT c)
{
    PT tmp;
    tmp.x=tmp.y=1e9+1;

    if(abs(signedArea(a,c,tmp))+abs(signedArea(b,c,tmp))==abs(signedArea(a,b,tmp))) return true;
    return false;
}

int main()
{
    FastIO;

    LL t=1,n,xx,yy;
    cin>>t;
    while(t--)
    {
        cin>>n;

        vector<PT>points;
        for(LL i=0; i<n*2; i++)
        {
            cin>>xx>>yy;
            PT tmp;
            tmp.x=xx;
            tmp.y=yy;
            points.push_back(tmp);
        }

        bool invalid=true;
        for(LL i=1; i<n*2; i++)
        {
            map<LL,vector<pair<PT,LL>>>mpp;
            mpp[0].push_back({points[0],1});
            mpp[0].push_back({points[i],i+1});

            bool valid=true;
            for(LL j=1; j<n*2; j++)
            {
                if(j==i) continue;

                LL val=signedArea(points[0], points[i], points[j]);
                if(val==0 and isInside(points[0], points[i], points[j]))
                {
                    valid=false;
                    break;
                }

                mpp[val].push_back({points[j],j+1});
            }

            vector<pair<LL,LL>>ans;
            for(auto it: mpp)
            {
                LL syz=it.second.size();
                if(syz%2==1)
                {
                    valid=false;
                    break;
                }

                vsort(it.second);
                for(LL i=1; i<syz; i+=2)
                {
                    ans.push_back({it.second[i-1].second,it.second[i].second});
                }
            }

            if(!valid) continue;

            invalid=false;
            for(LL i=0; i<n; i++)
            {
                cout<<ans[i].first<<" "<<ans[i].second<<"\n";
            }
            break;
        }

        if(invalid) cout<<"-1\n";
    }

    return 0;
}
