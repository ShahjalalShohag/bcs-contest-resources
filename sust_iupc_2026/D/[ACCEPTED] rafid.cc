#include <bits/stdc++.h>

using namespace std;

typedef long long Ti;

Ti ask(Ti m, Ti v) {
	cout << "? " << m << " " << v << "\n";
	fflush(stdout);

	Ti rsp;
	assert(cin >> rsp);
	assert(rsp == 0 || rsp == 1);
	return rsp;
}

void sanitize_ans(Ti a, Ti b) {
	const static Ti MAX = (1ll << 60) - 1;
	const static Ti MIN = 0;
	assert(a < b && a >= MIN && b <= MAX);
}

void ans(Ti a, Ti b) {
	sanitize_ans(a, b);
	cout << "! " << a << " " << b << "\n";
	fflush(stdout);
}

void solve() {
	const static Ti BITS = 60;

	// Find the MSB with mismatch. That would differentiate b from a.
	Ti df = BITS - 1;
	while (df > 0) {
		Ti q = 1ll << df;
		Ti c = ask(q, q);
		if (c == 1) {
			break;
		}
		df--;
	}

	// Initial assumptions.
	Ti a = 0;
	Ti b = 1ll << df;

	// Find out the more significant bits of a, b after [df]. They should be
	// the same for a and b since they differ at [df].
	for (Ti i = df+1; i < BITS; i++) {
		Ti q = (1ll << i) | (1ll << df);
		Ti c = ask(q, q);
		if (c == 0) {
			continue;
		}
		a |= (1ll << i);
		b |= (1ll << i);
	}

	// For each a and b, find out the lower bits after [df].
	for (Ti i = df-1; i >= 0; i--) {
		Ti qb = (1ll << i) | (1ll << df);
		Ti cb = ask(qb, qb);
		if (cb == 1) {
			b |= (1ll << i);
		}

		Ti qa = (1ll << i);
		Ti ca = ask(qa, qa);
		ca ^= cb; // True [ca].
		if (ca == 1) {
			a |= (1ll << i);
		}
	}

	ans(a, b);
}

int main() {
	Ti t;
	assert(cin >> t);
	assert(t >= 1 && t <= 1000);

	while (t--) {
		solve();
	}

	string token;
	assert(!(cin >> token));

	return 0;
}
