#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
static bitset<MAXN+1> M[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<pair<int,int>> edges(n-1);
        for(int i = 0; i < n-1; i++){
            cin >> edges[i].first >> edges[i].second;
            --edges[i].first;
            --edges[i].second;
        }
        
        if(n > MAXN){
            cout << -1 << "\n";
            continue;
        }
        
        for(int i = 0; i < n; i++){
            M[i].reset();
        }

        for(int e = 0; e < n-1; e++){
            auto [u,v] = edges[e];
            M[u].flip(e);
            M[v].flip(e);
        }
        
        for(int i = 0; i < n; i++){
            if(a[i]&1) M[i].flip(n-1);
        }

        int m = n-1;
        int row = 0;
        vector<int> where(m, -1);
        for(int col = 0; col < m && row < n; col++){
            int sel = -1;
            for(int i = row; i < n; i++){
                if(M[i].test(col)){
                    sel = i;
                    break;
                }
            }
            if(sel < 0) continue;
            swap(M[row], M[sel]);
            where[col] = row;

            for(int i = 0; i < n; i++){
                if(i != row && M[i].test(col)){
                    M[i] ^= M[row];
                }
            }
            row++;
        }

        bool ok = true;
        for(int i = row; i < n; i++){
            if(M[i].test(n-1)){
                ok = false;
                break;
            }
        }
        if(!ok){
            cout << -1 << "\n";
            continue;
        }

        vector<int> x(m,0);
        for(int i = 0; i < m; i++){
            if(where[i] != -1){
                x[i] = M[where[i]].test(n-1);
            }
        }
        
        int ans = 0;
        for(int i = 0; i < m; i++){
            ans += x[i];
        }
        cout << ans << "\n";
    }
    return 0;
}
