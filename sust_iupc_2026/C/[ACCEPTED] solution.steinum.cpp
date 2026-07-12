#include <bits/stdc++.h>
using namespace std;


#define ll long long
int sign(ll x) { return (x > 0) - (x < 0); }
#define point pair<ll, ll>
#define x first
#define y second
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
ll operator * (point a, point b) { return (a.x * b.y - a.y * b.x); }
ll operator | (point a, point b) { return (a.x * b.x + a.y * b.y); }
int orientation(point a, point b, point c) { return sign((b - a) * (c - a)); }

vector<point> convex_hull(vector<point> p) {
	int sz = 0 , n = p.size();
	sort(p.begin(), p.end()); if(n<3)return p;
	vector<point> hull(n + n);
	for(int i = 0; i < n; ++i) {
		while (sz > 1 and orientation(hull[sz - 2], hull[sz - 1], p[i]) <= 0) --sz;
		hull[sz++] = p[i];
	}
	for(int i = n - 2, j = sz + 1; i >= 0; --i) {
		while (sz >= j and orientation(hull[sz - 2], hull[sz - 1], p[i]) <= 0) --sz;
		hull[sz++] = p[i];
	} hull.resize(sz - 1); return hull;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t; cin >> t; while(t--) {
		int n; cin >> n;
		vector<point> v(2 * n);
		for(auto &[x, y]: v) cin >> x >> y;
		auto p = convex_hull(v);
		vector<tuple<ll, ll, int>> idx(2 * n);
		int ok = 0;
		for(int i = 0, sz = (int)p.size(); i < sz; i++) {
			point &a = p[i], &b = (i + 1 == sz? p[0]: p[i + 1]);
			for(int j = 0; j < 2 * n; j++) idx[j] = {(v[j] - a) * (b - a), (v[j] - a) | (b - a), j + 1};
			sort(idx.begin(), idx.end());
			int flag = 1;
			for(int j = 0; j < 2 * n; j += 2) {
				if(get<0>(idx[j]) != get<0>(idx[j + 1])) {
					flag = 0;
					break;
				}
			}
			if(flag) {
				ok = 1;
				break;
			}
		}
		if(ok) {
			for(int i = 0; i < 2 * n; i += 2) cout << get<2>(idx[i]) << ' ' << get<2>(idx[i + 1]) << '\n';
		} else {
			cout << -1 << '\n';
		}
	}
	return 0;
}