#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>
#include <chrono>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(a.begin(), a.end(), std::default_random_engine(seed));

    int min_score = INT_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && j <= i + 5000; j++) {
            int current_xor = a[i] ^ a[j];
            if (current_xor < min_score) {
                min_score = current_xor;
            }
        }
    }

    cout << min_score << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}