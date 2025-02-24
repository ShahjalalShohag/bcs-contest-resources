#include<bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
#define endl '\n'

#define pi acos(-1)

struct Polygon{
    double n;
    double s;
    Polygon(int a, int b) {
        n = a;
        s = b;
    }
    double getCircumRadius() {
        return (double)s/( 2.0 * sin(pi/n) );
    }

    double getApothem() {
        return (double)s/( 2.0 * tan(pi/n) );
    }

    double getArea(){
        return (double)0.5 * n * s * getApothem();
    }

    double getInscribedCircleArea() {
        double r = getApothem();
        return (double)pi*r*r;
    }

};

double getCoveredArea(Polygon top, Polygon bottom) {
    double r = top.getApothem();
    double a = bottom.getApothem();
    double t_area = 0.5 * sqrtl( r*r - a*a ) * a;
    double phi = (pi/bottom.n - acos(a/r));
    double arc_area = phi * r*r/2.0;
    return 2.0*( t_area + arc_area );
}

void solve(){

    int a,b,c,d;
    cin>>a>>b>>c>>d;
    Polygon top(a,b), bottom(c,d);
    

    double area;
    if( top.getApothem() >= bottom.getCircumRadius() ){
        area = 0;
    } else if( top.getApothem() <= bottom.getApothem() ){
        area = bottom.getArea() - top.getInscribedCircleArea();
    } else {
        double c_area = getCoveredArea(top,bottom) * bottom.n;
        area = bottom.getArea() - c_area;
    }
    cout<<area<<endl;
}

int main() {
    FASTIO;
    cout<<fixed<<setprecision(10);
    int tc;
    cin>>tc;
    while(tc--) solve();
}
