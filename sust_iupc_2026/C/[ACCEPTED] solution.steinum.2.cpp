#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define point pair<ll, ll>
#define x first
#define y second
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
ll operator * (point a, point b) { return (a.x * b.y - a.y * b.x); }
ll operator | (point a, point b) { return (a.x * b.x + a.y * b.y); }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t; cin >> t; while(t--) {
		int n; cin >> n;
		vector<point> v(2 * n);
		for(auto &[x, y]: v) cin >> x >> y;
		vector<tuple<ll, ll, int>> idx(2 * n);
		int ok = 0;
		for(int i = 1; i < 2 * n; i++) {
			point &a = v[0], &b = v[i];
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