#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while(T--){
        int n,m;
        cin >> n >> m;
        int k = min(n,m);
        int ans = min(2*k, max(n,m));
        cout << ans << "\n";

        if(n <= m){
            // direct build n x m
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    int x = (j <= n ? min(i,j) : j);
                    cout << x << (j==m?'\n':' ');
                }
            }
        } else {
            // build A of size m x n, then transpose
            vector<vector<int>> A(m+1, vector<int>(n+1));
            for(int i = 1; i <= m; i++){
                for(int j = 1; j <= n; j++){
                    A[i][j] = (j <= m ? min(i,j) : j);
                }
            }
            // transpose into an n x m grid
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    cout << A[j][i] << (j==m?'\n':' ');
                }
            }
        }
    }
    return 0;
}
