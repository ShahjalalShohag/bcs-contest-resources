#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int MAX_VAL = 20000000;

// Global storage
vector<pair<int, int>> twins;
vector<bool> is_prime;

// Sieve to find disjoint twin primes
void sieve() {
    is_prime.assign(MAX_VAL + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int p = 2; p * p <= MAX_VAL; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_VAL; i += p)
                is_prime[i] = false;
        }
    }

    // Collect strictly disjoint Twin Prime pairs
    // We increment p extra to ensure sets like {3,5} and {5,7} don't overlap
    for (int p = 3; p + 2 <= MAX_VAL; p++) {
        if (is_prime[p] && is_prime[p+2]) {
            twins.push_back({p, p+2});
            p += 2; 
        }
    }
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    // We need 1 variable point for every 4 triangles
    int variable_points_count = (n + 3) / 4; 
    
    // 1. Output total number of points (4 base + variable)
    cout << 4 + variable_points_count << "\n";
    
    // 2. Output the 4 Base Points (Fixed 2x2 square at origin)
    // Indices: 1=(0,0), 2=(2,0), 3=(0,2), 4=(2,2)
    cout << "0 0\n";
    cout << "2 0\n";
    cout << "0 2\n";
    cout << "2 2\n";

    // Store triangles to print after all points are outputted
    vector<tuple<int, int, int>> triangles;
    triangles.reserve(n);

    int twin_idx = 0;

    // 3. Output Variable Points and generate Triangles
    for (int k = 0; k < variable_points_count; k++) {
        if (twin_idx + 1 >= (int)twins.size()) break;

        // Get two disjoint pairs of twin primes
        pair<int, int> t1 = twins[twin_idx++];
        pair<int, int> t2 = twins[twin_idx++];

        // Calculate coordinates
        // x = p1 + 2  => Distances to x=0 and x=2 are (p1+2) and p1
        // y = p2 + 2  => Distances to y=0 and y=2 are (p2+2) and p2
        long long x = t1.first + 2;
        long long y = t2.first + 2;
        
        cout << x << " " << y << "\n";
        
        // Current point index (starts at 5)
        int idx = 5 + k;
        
        // Generate up to 4 triangles for this point
        // Triangle 1: Base (0,0)-(0,2) [Idx 1,3], Height x. Area = p1+2
        triangles.emplace_back(idx, 1, 3);
        
        // Triangle 2: Base (2,0)-(2,2) [Idx 2,4], Height x-2. Area = p1
        triangles.emplace_back(idx, 2, 4);
        
        // Triangle 3: Base (0,0)-(2,0) [Idx 1,2], Height y. Area = p2+2
        triangles.emplace_back(idx, 1, 2);
        
        // Triangle 4: Base (0,2)-(2,2) [Idx 3,4], Height y-2. Area = p2
        triangles.emplace_back(idx, 3, 4);
    }

    // 4. Output the triangles
    for (int i = 0; i < n; i++) {
        cout << get<0>(triangles[i]) << " " 
             << get<1>(triangles[i]) << " " 
             << get<2>(triangles[i]) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}