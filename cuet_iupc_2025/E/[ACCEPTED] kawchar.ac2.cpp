#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 300005

typedef long long ll;
typedef long double ld;

const ll INF = (ll)1e18;
const ld eps = 1e-9;
const ld PI = acos((double)-1.0);
int sign(ld x) { return (x > eps) - (x < -eps); }

double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }

ld get_angle(ld x, ld y) {
    ld a = atan2(y, x);
    if (a < 0) a += 2*PI;
    return a;
}

struct pt{
    ll x, y, v;
    ld a;
    pt() {}
    pt(ll _x, ll _y, ll _v) {
        x = _x; y = _y; v = _v;
        a = get_angle(x, y);
    }
};

bool operator<(pt p, pt q) {
    return p.a < q.a;
}

vector<ll> cum_sum;

ll get_sum(int l, int r) {
    ll sum = cum_sum[r];
    if(l > 0) sum -= cum_sum[l - 1];
    return abs(sum);
}

void solve() {
    int n, r, A; 
    cin >> n >> r >> A;
    ld max_angle = 2 * (ld)A / (1LL * r * r);
    vector< pt > points, points_init;
    for (int i = 0; i < n; i++) {
        int x, y, v; 
        cin >> x >> y >> v;
        points_init.push_back(pt(x, y, v));
    }
    sort(points_init.begin(), points_init.end());
    points.push_back(points_init[0]);
    for (int i = 1; i < n; i++) {
        if(abs(points_init[i].a - points_init[i - 1].a) > eps)
            points.push_back(points_init[i]);
        else
            points[points.size()-1].v += points_init[i].v;
    }
    n = points.size();
    for (int i = 0; i < n; i++) {
        auto tmp = points[i];
        tmp.a += 2*PI;
        points.push_back(tmp);
    }
    
    cum_sum.clear();
    ll sum = 0;
    for (auto p : points) {
        sum += p.v;
        cum_sum.push_back(sum);
    }

    deque<int> min_q, max_q;

    ll mx_sum = 0;
    for (int l = 0, r = 0; l < n; l++) {
        while(r < points.size() && (r - l) < n && (points[r].a - points[l].a) <= (max_angle + eps)) {
            while(min_q.size() && cum_sum[min_q.back()] >= cum_sum[r]) min_q.pop_back();
            min_q.push_back(r);

            while(max_q.size() && cum_sum[max_q.back()] <= cum_sum[r]) max_q.pop_back();
            max_q.push_back(r);
            r++;
        }
        
        while(min_q.size() && min_q.front() < l) min_q.pop_front();
        while(max_q.size() && max_q.front() < l) max_q.pop_front();


        if (min_q.size()) {
            mx_sum = max({mx_sum, get_sum(l, max_q.front()), get_sum(l, min_q.front())});
        }

    }
    cout << mx_sum << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}