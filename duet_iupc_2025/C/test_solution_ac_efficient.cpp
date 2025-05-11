#include <bits/stdc++.h>
using namespace std;

#define ll long long int

struct pt
{
    int x, y;
    bool operator<(pt p)
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

ll cross_product(pt O, pt A, pt B)
{
    return (ll)(A.x - O.x) * (ll)(B.y - O.y) - (ll)(A.y - O.y) * (ll)(B.x - O.x);
}
vector<pt> convex_hull(vector<pt> A)
{
    int n = A.size(), k = 0;
    if (n <= 3)
        return A;
    vector<pt> ans(2 * n);
    sort(A.begin(), A.end());
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0)
            k--;
        ans[k++] = A[i];
    }
    for (size_t i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) <= 0)
            k--;
        ans[k++] = A[i - 1];
    }
    ans.resize(k - 1);

    return ans;
}
ll mul(int a, int b){
    return (ll)a * (ll)b;
}

ll triangle_area_2(pt a, pt b, pt c){
    return abs(mul(a.x, b.y)+mul(b.x,c.y)+mul(c.x,a.y)-mul(b.x,a.y)-mul(c.x,b.y)-mul(a.x,c.y));
}

int get_pos(vector<pt>& a, pt b){
    for(int i=0;i<(int)a.size();i++){
        if(a[i].x==b.x && a[i].y==b.y){
            return i+1;
        }
    }
    return 0;
}

int main()
{

    int t;
    scanf("%d", &t);

    while(t--){
        int n;
        scanf("%d", &n);
        if(!n) break;

        vector<pt> points, cnv_points;
        for(int i=0;i<n;i++){
            pt tmp;
            scanf("%d %d", &tmp.x, &tmp.y);
            points.push_back(tmp);
        }
        cnv_points = convex_hull(points);

        if(cnv_points.size() == points.size()){
            printf("-1\n");
            continue;
        }
        
        pair<int, pt> mid_point;
        for(int i=0;i<n;i++){
            bool flag=0;
            for(int j=0;j<(int)cnv_points.size();j++){
                if(points[i].x==cnv_points[j].x && points[i].y==cnv_points[j].y){
                    flag=1;
                    break;
                }
            }
            if(!flag){
                mid_point={i, points[i]};
                break;
            }
        }

        pt bound[3];
        while(cnv_points.size()>=3){
            ll len=cnv_points.size();
            ll p=triangle_area_2(cnv_points[0],cnv_points[len-1], cnv_points[len-2]);
            ll a=triangle_area_2(mid_point.second,cnv_points[0], cnv_points[len-1]);
            ll b=triangle_area_2(mid_point.second,cnv_points[len-1], cnv_points[len-2]);
            ll c=triangle_area_2(mid_point.second,cnv_points[len-2], cnv_points[0]);
            if(a+b+c==p){
                bound[0]=cnv_points[0];
                bound[1]=cnv_points[len-1];
                bound[2]=cnv_points[len-2];
                break;
            }
            cnv_points.pop_back();
        }
        printf("%d %d %d %d\n", mid_point.first+1, get_pos(points, bound[0]), 
            get_pos(points, bound[1]), get_pos(points, bound[2]));
    }

    return 0;
}