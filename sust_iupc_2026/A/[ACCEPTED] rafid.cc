#include <bits/stdc++.h>

using namespace std;

typedef long long Ti;

struct Range {
	Ti l, r;
};

const Ti MOD = 998244353;

// Finds the range [l, r] for each index i such that
// a[i] is the maximum number in [l, r].
vector<Range> find_ranges(const vector<Ti>& a) {
	Ti n = a.size();
	vector<Range> ranges(n);
	stack<Ti> ls, rs;
	for (Ti i = 0; i < n; i++) {
		while (!ls.empty() && a[ls.top()] < a[i]) {
			ls.pop();
		}
		if (ls.empty()) {
			ranges[i].l = 0;
		} else {
			ranges[i].l = ls.top() + 1;
		}
		ls.push(i);
	}
	for (Ti i = n-1; i >= 0; i--) {
		while (!rs.empty() && a[rs.top()] < a[i]) {
			rs.pop();
		}
		if (rs.empty()) {
			ranges[i].r = n - 1;
		} else {
			ranges[i].r = rs.top() - 1;
		}
		rs.push(i);
	}
	return ranges;
}

Ti solve(const vector<Ti>& a, const vector<Ti>& b) {
	auto ranges = find_ranges(a);
	Ti n = a.size();

	vector<Ti> demand(n, 0);
	for (const Ti v : b) {
		demand[v]++;
	}
	vector<Ti> pref_demand(n+1, 0);
	for (Ti i = 0; i < n; i++) {
		pref_demand[i+1] = pref_demand[i] + demand[a[i]];
	}

	Ti res = 1;
	for (Ti i = 0; i < n; i++) {
		Ti v = a[i];
		Ti size = ranges[i].r - ranges[i].l + 1;
		Ti total_demand = pref_demand[ranges[i].r + 1] - pref_demand[ranges[i].l];
		Ti filled = total_demand - demand[v];
		Ti open = size - filled;
		for (Ti k = 0; k < demand[v]; k++) {
			Ti options = open - k;
			if (options <= 0) {
				return 0;
			}
			res = (res * options) % MOD;
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	Ti t;
	assert(cin >> t);
	assert(t >= 1 && t <= 10000);

	Ti n_sum = 0;

	while (t--) {
		Ti n;
		assert(cin >> n);
		assert(n >= 1 && n <= 300000);

		n_sum += n;
		assert(n_sum <= 300000);

		vector<Ti> a(n), ca(n);
		for (Ti& v : a) {
			assert(cin >> v);
			assert(v >= 1 && v <= n);
			v--;
			ca[v]++;
		}
		for (const Ti v : ca) {
			assert(v == 1);
		}

		vector<Ti> b(n);
		for (Ti& v : b) {
			assert(cin >> v);
			assert(v >= 1 && v <= n);
			v--;
		}

		Ti res = solve(a, b);
		cout << res << "\n";
	}

	string token;
	assert(!(cin >> token));

	return 0;
}
