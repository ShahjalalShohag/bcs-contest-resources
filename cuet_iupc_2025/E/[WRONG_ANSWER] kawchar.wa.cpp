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

struct Info {
    ll sum, pref, suf, mx;
    Info(): sum(0), pref(-INF), suf(-INF), mx(-INF) {} 
    Info(ll v): sum(v), pref(v), suf(v), mx(v) {}
};

Info merge(Info L, Info R){
    if(L.mx == -INF) return R;
    if(R.mx == -INF) return L;
    Info res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suf = max(R.suf, R.sum + L.suf);
    res.mx = max({L.mx, R.mx, L.suf + R.pref});
    return res;
}

struct SegTreeMax {
    int n;
    vector<Info> t;
    vector<ll> v;
    SegTreeMax(vector<ll> &a) {
        v = a; n = v.size(); 
        t.assign(4*n, Info());
        build(1, 0, n - 1);
    }

    void build(int node, int l, int r) {
        if (l == r) { t[node] = Info(v[l]); return;}
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    Info query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return Info();
        if (ql <= l && r <= qr) return t[node];
        int mid = (l+r)/2;
        Info L = query(node*2, l, mid, ql, qr);
        Info R = query(node*2+1, mid+1, r, ql, qr);
        return merge(L, R);
    }

    ll query(int l, int r) { return query(1, 0, n-1, l, r).mx; }
};

void solve() {
    int n, r, A; 
    cin >> n >> r >> A;
    ld max_angle = 2 * (ld)A / (1LL * r * r);
    vector< pt > points;
    for (int i = 0; i < n; i++) {
        int x, y, v; 
        cin >> x >> y >> v;
        points.push_back(pt(x, y, v));
    }
    sort(points.begin(), points.end());
    for (int i = 0; i < n; i++) {
        auto tmp = points[i];
        tmp.a += 2*PI;
        points.push_back(tmp);
    }
    vector<ll> tmp;
    for(auto p : points) tmp.push_back(p.v);
    SegTreeMax stMax(tmp);
    
    tmp.clear();
    for(auto p : points) tmp.push_back(-p.v);
    SegTreeMax stMin(tmp);

    ll mx_sum = 0;
    for (int l = 0, r = 0; l < n; l++) {
        while(r + 1 < points.size() && (points[r + 1].a - points[l].a) <= (max_angle + eps))
            r++;

        r = max(r, l);
        int R = min(r, l + n - 1);
        
        // cout << l << " ? " << R << "\n";
        mx_sum = max({mx_sum, stMax.query(l, R), stMin.query(l, R)});

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