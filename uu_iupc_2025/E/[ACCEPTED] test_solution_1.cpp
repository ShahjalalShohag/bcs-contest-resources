#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define all(x) x.begin(),x.end()
#define Max 10000000000000000

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using min_heap=priority_queue<T, vector<T>, greater<T>>;

struct point {
    double x, y;
    point(){
        x = 0;
        y = 0;
    }
    point(double x, double y): x(x), y(y) {}
};

struct line {
    double a, b, c;
    line(){
        a = 0;
        b = 1;
        c = 0;
    }
    line(double a, double b, double c): a(a), b(b), c(c) {}
};

double getDist(point a, point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

line getParallel(point a, point b, double h){
    line edge;
    if(a.x == b.x)
        edge = line(1, 0, -a.x);
    else if(a.y == b.y)
        edge = line(0, -1, a.y);
    else{
        double m = (a.y - b.y) / (a.x - b.x);
        double c = a.y - m * a.x;
        edge = line(m, -1, c);
    }

    ll sign = 1;
    if(a.x > b.x || (a.x == b.x && a.y > b.y)) sign = -1;

    double retC = edge.c + sign * h * sqrt(edge.a * edge.a + edge.b * edge.b);
    return line(edge.a, edge.b, retC);
}

ll getSide(line p, point a){
    double ret = p.a * a.x + p.b * a.y + p.c;
    if(ret == 0) return 0;
    return ret / fabs(ret);
}

point getIntersectionPoint(line p, line q){
    double det = p.a * q.b - q.a * p.b;

    double x = (p.b * q.c - q.b * p.c) / det;
    double y = (q.a * p.c - p.a * q.c) / det;

    return point(x, y);
}

int main()
{

    ll n;
    cin>>n;

    point inpPoints[n];
    for(ll i = 0; i < n; i++) 
        cin>>inpPoints[i].x>>inpPoints[i].y;

    double l = 0, r = 1e12;
    for(ll loopCnt = 0; loopCnt <= 70; loopCnt++){
        double m = (l + r) / 2.0;

        vector<point> hull;
        bool delMask[n];
        for(ll i = 0; i < n; i++)
            hull.pb(inpPoints[i]);

        for(ll i = 0; i < n; i++){
            for(ll j = 0; j < hull.size(); j++) delMask[j] = 0;
            double d = getDist(inpPoints[i], inpPoints[(i + 1) % n]);
            double h = (2 * m) / d;
            line clipLine = getParallel(inpPoints[i], inpPoints[(i + 1) % n], h);

            for(ll j = 0; j < hull.size(); j++){
                if(getSide(clipLine, inpPoints[i]) != getSide(clipLine, hull[j]) && getSide(clipLine, hull[j]))
                    delMask[j] = 1;
            }
            
            vector<point> tmp;
            for(ll j = 0; j < hull.size(); j++){
                ll len = hull.size();
                if(!delMask[j]){
                    tmp.pb(hull[j]);
                    continue;
                }

                ll prevPointIdx = (j + len - 1) % len;
                ll nextPointIdx = (j + 1) % len;

                if(!delMask[prevPointIdx] && getSide(clipLine, hull[prevPointIdx])){
                    line edge = getParallel(hull[prevPointIdx], hull[j], 0);
                    point intersectionPoint = getIntersectionPoint(clipLine, edge);
                    tmp.pb(intersectionPoint);
                }
                if(!delMask[nextPointIdx] && getSide(clipLine, hull[nextPointIdx])){
                    line edge = getParallel(hull[j], hull[nextPointIdx], 0);
                    point intersectionPoint = getIntersectionPoint(clipLine, edge);
                    tmp.pb(intersectionPoint);
                }
            }
            hull = tmp;
        }
        if(hull.size()) r = m;
        else l = m;
    }

    cout<<fixed<<setprecision(10)<<l<<endl;

    return 0;
}