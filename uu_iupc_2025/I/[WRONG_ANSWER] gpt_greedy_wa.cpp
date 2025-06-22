// Greedy WA for “Statue on a Permutation”
// Assign top values to 'A' and bottom values to 'B' in one pass.

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> p(n);
        int low = 1, high = n;
        for(int i = 0; i < n; i++){
            if(s[i] == 'A'){
                p[i] = high--;
            } else {
                p[i] = low++;
            }
        }
        for(int i = 0; i < n; i++){
            cout << p[i] << (i+1<n ? ' ' : '\n');
        }
    }
    return 0;
}
