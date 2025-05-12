#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

struct Point {
    int x, y, index;
};

long long cross_product(const Point& p1, const Point& p2, const Point& p3) {
    return 1LL * (p2.x - p1.x) * (p3.y - p1.y) - 1LL * (p2.y - p1.y) * (p3.x - p1.x);
}

bool is_point_inside_triangle(const Point& p, const Point& a, const Point& b, const Point& c) {
    long long c1 = cross_product(a, b, p);
    long long c2 = cross_product(b, c, p);
    long long c3 = cross_product(c, a, p);
    
    return (c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0);
}

void solve(){
    int n;
    cin >> n;
    vector<Point> pts(n);
    for(int i=0;i<n;i++){
        cin >> pts[i].x >> pts[i].y;
        pts[i].index = i;
    }

    int m = min(20, n);

    // Phase 1: i in [0,m), j,k,l in [0,m)
    for(int i=0;i<m;i++){
      for(int j=i+1;j<m;j++){
        for(int k=j+1;k<m;k++){
          for(int l=k+1;l<m;l++){
            if(is_point_inside_triangle(pts[i], pts[j], pts[k], pts[l])){
              cout<<pts[i].index+1<<" "
                  <<pts[j].index+1<<" "
                  <<pts[k].index+1<<" "
                  <<pts[l].index+1<<"\n";
              return;
            }
          }
        }
      }
    }

    // Phase 2: i in [0,m), j,k,l in [n-m,n)
    int start = max(0, n-m);
    for(int i=0;i<m;i++){
      for(int j=start;j<n;j++){
        for(int k=j+1;k<n;k++){
          for(int l=k+1;l<n;l++){
            if(is_point_inside_triangle(pts[i], pts[j], pts[k], pts[l])){
              cout<<pts[i].index+1<<" "
                  <<pts[j].index+1<<" "
                  <<pts[k].index+1<<" "
                  <<pts[l].index+1<<"\n";
              return;
            }
          }
        }
      }
    }

    // Phase 3: random sample of up to 20 distinct indices, sorted
    mt19937_64 rng(chrono::high_resolution_clock::now()
                      .time_since_epoch().count());
    uniform_int_distribution<int> dist(0,n-1);

    vector<int> sample;
    sample.reserve(m);
    vector<bool> used(n,false);
    while((int)sample.size()<m){
      int x = dist(rng);
      if(!used[x]){
        used[x]=true;
        sample.push_back(x);
      }
    }
    sort(sample.begin(), sample.end());

    for(int ii=0;ii<m;ii++){
      int i = sample[ii];
      for(int jj=ii+1;jj<m;jj++){
        int j = sample[jj];
        for(int kk=jj+1;kk<m;kk++){
          int k = sample[kk];
          for(int ll=kk+1;ll<m;ll++){
            int l = sample[ll];
            if(is_point_inside_triangle(pts[i], pts[j], pts[k], pts[l])){
              cout<<pts[i].index+1<<" "
                  <<pts[j].index+1<<" "
                  <<pts[k].index+1<<" "
                  <<pts[l].index+1<<"\n";
              return;
            }
          }
        }
      }
    }

    // none found
    cout<<"-1\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
