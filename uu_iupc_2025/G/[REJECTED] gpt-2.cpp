#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> A(n);
        for (int &x : A) cin >> x;

        vector<int> l(n), r(n); // boundaries where A[i] is max
        stack<int> s;

        // Previous greater (strictly)
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && A[s.top()] < A[i]) s.pop();
            l[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }

        while (!s.empty()) s.pop();

        // Next greater or equal
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && A[s.top()] <= A[i]) s.pop();
            r[i] = s.empty() ? n : s.top();
            s.push(i);
        }

        // Count how many subarrays A[i] is max of
        vector<long long> contrib(n + 2, 0);
        for (int i = 0; i < n; ++i) {
            long long count = 1LL * (i - l[i]) * (r[i] - i);
            contrib[A[i]] += count;
        }

        // Now compute MEX of max values for all subarrays
        // Using prefix sum: for each x, if contrib[x] > 0, then x is in MEX array
        long long result = 0;
        set<int> present;
        for (int x = 0; x <= n + 1; ++x) {
            if (contrib[x] == 0) {
                result += 1LL * x * (n - x + 1); // MEX of all future subarrays will include this x
                break;
            }
        }

        // Actually sum the full MM(A[i..j]) using contribution:
        // For each value x, it contributes x * (number of subarrays where it is the MEX of max)
        // Track MEX from 0 upwards
        set<int> appeared;
        int mex = 0;
        for (int x = 0; x <= n + 1; ++x) {
            if (contrib[x] == 0) break;
            result += contrib[x] * mex;
            appeared.insert(x);
            while (appeared.count(mex)) ++mex;
        }

        cout << result << '\n';
    }

    return 0;
}
