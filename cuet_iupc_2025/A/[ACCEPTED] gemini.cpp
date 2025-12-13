#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    long long n, m;
    int r1, c1, r2, c2;
    
    // Read input
    if (!(cin >> n >> m >> r1 >> c1 >> r2 >> c2)) return;

    // 1. Total Parity Check
    // If n * m is odd, the number of 1s (nm - 2) is odd.
    // Dominoes always remove an even number of 1s.
    if ((n % 2 != 0) && (m % 2 != 0)) {
        cout << "NO" << "\n";
        return;
    }

    // 2. Color Parity Check
    // In a checkerboard coloring, the two removed cells must be of opposite colors.
    // Color can be determined by (row + col) % 2.
    int color1 = (r1 + c1) % 2;
    int color2 = (r2 + c2) % 2;

    if (color1 == color2) {
        cout << "NO" << "\n";
        return;
    }

    // 3. 1D Geometric Constraint Check
    // If the grid is just a single line, we must ensure the segments created 
    // by the holes have even lengths.
    
    // Case: Single Row
    if (n == 1) {
        if (c1 > c2) swap(c1, c2); // Ensure c1 is the first hole
        // The segment of 1s before c1 has length (c1 - 1).
        // This length must be even.
        if ((c1 - 1) % 2 != 0) {
            cout << "NO" << "\n";
        } else {
            cout << "YES" << "\n";
        }
        return;
    }

    // Case: Single Column
    if (m == 1) {
        if (r1 > r2) swap(r1, r2); // Ensure r1 is the first hole
        // The segment of 1s before r1 has length (r1 - 1).
        // This length must be even.
        if ((r1 - 1) % 2 != 0) {
            cout << "NO" << "\n";
        } else {
            cout << "YES" << "\n";
        }
        return;
    }

    // 4. General Case (n > 1 and m > 1)
    // For a rectangular grid with width > 1, having different colored holes 
    // and even total area is sufficient for a valid tiling.
    cout << "YES" << "\n";
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}