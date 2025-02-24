#include <bits/stdc++.h>
using namespace std;
#define double long double
const double pi = acos(-1.0), eps = 1e-15;
inline int sign(double x) { return (x > eps) - (x < -eps); }
int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << setprecision(10) << fixed;
	int t; cin >> t; while(t--) {
		int nt, at, nb, ab; cin >> nt >> at >> nb >> ab;
		double tt = pi / nt, tb = pi / nb;
		double r = (at * .5) / tan(tt), d = (ab * .5) / tan(tb);
		if(sign((ab * .5) / sin(tb) - r) <= 0) {
			cout << 0 << '\n';
		} else {
			double intersection = pi * r * r;
			if(sign(r - d) > 0) {
				double a = acos(d / r);
				intersection = (r * r * (tb - a) + d * sqrt(r * r - d * d)) * nb;
			}
			double ans = (d * ab / 2) * nb - intersection;
			cout << ans << '\n';
		}
	}
	return 0;
}