// brute_bfs_tle.cpp
// Intentionally slow brute-force (BFS) for "Delete Local Maxima".
// Correct but exponential-time and memory-heavy — will TLE on large tests.
// DO NOT add any fast-paths or size guards if you want a TLE verdict.

#include <bits/stdc++.h>
using namespace std;

// encode vector<int> as comma-separated string: "1,2,3"
static string encode(const vector<int>& v) {
    string s;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s.push_back(',');
        s += to_string(v[i]);
    }
    return s;
}

static vector<int> decode(const string &s) {
    vector<int> v;
    int cur = 0;
    bool innum = false;
    for (char c : s) {
        if (c == ',') {
            v.push_back(cur);
            cur = 0;
            innum = false;
        } else if (c >= '0' && c <= '9') {
            cur = cur * 10 + (c - '0');
            innum = true;
        }
    }
    if (innum) v.push_back(cur);
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        // BFS over states (encoded as strings). Start from initial permutation.
        queue<string> q;
        unordered_set<string> seen;
        string start = encode(p);
        q.push(start);
        seen.insert(start);

        bool ok = false;
        while (!q.empty()) {
            string cur_s = q.front(); q.pop();
            vector<int> cur = decode(cur_s);
            if ((int)cur.size() == 2) {
                ok = true;
                break;
            }
            int m = (int)cur.size();
            // generate all next states by removing any interior local maximum
            for (int i = 1; i + 1 < m; ++i) {
                if (cur[i] > cur[i-1] && cur[i] > cur[i+1]) {
                    vector<int> nxt;
                    nxt.reserve(m-1);
                    for (int j = 0; j < m; ++j) if (j != i) nxt.push_back(cur[j]);
                    string nxt_s = encode(nxt);
                    if (seen.insert(nxt_s).second) {
                        q.push(nxt_s);
                    }
                }
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}
