#include <bits/stdc++.h>
using namespace std;

#define ll long long int

int main()
{
    int t;
    scanf("%d", &t);

    assert(t>=1 && t<=1000);

    while(t--){
        int n;
        scanf("%d", &n);
        assert(n>=4 && n<=4000);

        vector<pair<int,int>> points(n);
        for(int i=0;i<n;i++){
            scanf("%d %d", &points[i].first, &points[i].second);
            assert(points[i].first>=1 && points[i].first<=500000);
            assert(points[i].second>=1 && points[i].second<=500000);
        }
        map<pair<pair<ll,int>,pair<ll,int>>, bool> ab;
        sort(points.begin(), points.end());
        for(int i=1;i<n;i++) assert(points[i]!=points[i-1]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(i==j) continue;
                int dx=points[i].first-points[j].first;
                int dy=points[i].second-points[j].second;
                ll a=(ll)points[j].first*(ll)points[i].second-(ll)points[i].first*(ll)points[j].second;
                ll b=-1*a;
                pair<pair<ll,int>,pair<ll,int>> tmp;
                if(dy==0){
                    ll gcd=__gcd(b,(ll)dx);
                    b/=gcd;
                    dx/=gcd;
                    if(dx<0) b*=-1, dx*=-1;
                    tmp = {{1e15, 0}, {b, dx}};
                }
                else if(dx==0){
                    ll gcd=__gcd(a,(ll)dy);
                    a/=gcd;
                    dy/=gcd;
                    if(dy<0) a*=-1, dy*=-1;
                    tmp = {{a, dy}, {1e15, 0}};
                }
                else{
                    int ad=dy;
                    ll gcd1=__gcd(a,(ll)ad);
                    a/=gcd1;
                    ad/=gcd1;
                    int bd=dx;
                    ll gcd2=__gcd(b,(ll)bd);
                    b/=gcd2;
                    bd/=gcd2;
                    if(ad<0) a*=-1, ad*=-1;
                    if(bd<0) b*=-1, bd*=-1;
                    tmp = {{a, ad}, {b, bd}};
                }
                assert(ab[tmp]==0);
                ab[tmp]=1;
            }
        }
    }
    printf("Everything is fine!!!");
    return 0;
}