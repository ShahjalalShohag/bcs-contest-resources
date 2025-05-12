#include <bits/stdc++.h>
using namespace std;

int n, m;
int N;              // n*m
int bestScore;
vector<int> bestGrid;
vector<int> grid_;  // size N

// Evaluate current grid_; update bestScore & bestGrid if improved
void evaluate(){
    // compute r_i
    vector<int> r(n, 0), c(m, 0);
    // since we only use values 1..N, we can use a small array for seen
    static bool seen[20]; // assume n*m <= 15
    // rows
    for(int i = 0; i < n; i++){
        fill(seen, seen+N+1, false);
        int cnt = 0;
        for(int j = 0; j < m; j++){
            int v = grid_[i*m + j];
            if(!seen[v]){
                seen[v] = true;
                cnt++;
            }
        }
        r[i] = cnt;
    }
    // cols
    for(int j = 0; j < m; j++){
        fill(seen, seen+N+1, false);
        int cnt = 0;
        for(int i = 0; i < n; i++){
            int v = grid_[i*m + j];
            if(!seen[v]){
                seen[v] = true;
                cnt++;
            }
        }
        c[j] = cnt;
    }
    // form S
    // the counts r[i],c[j] are each between 1 and max(n,m)
    int M = max(n,m);
    static bool seenCnt[20];
    fill(seenCnt, seenCnt+M+1, false);
    int distinct = 0;
    for(int x : r){
        if(!seenCnt[x]){
            seenCnt[x] = true;
            distinct++;
        }
    }
    for(int x : c){
        if(!seenCnt[x]){
            seenCnt[x] = true;
            distinct++;
        }
    }
    if(distinct > bestScore){
        bestScore = distinct;
        bestGrid = grid_;
    }
}

// backtrack over every assignment of grid_[0..N)
void dfs(int pos){
    if(pos == N){
        evaluate();
        return;
    }
    // try every possible value 1..N
    for(int v = 1; v <= N; v++){
        grid_[pos] = v;
        dfs(pos+1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        cin >> n >> m;
        N = n*m;
        // guard so we don't blow up
        if(N > 7){
            // too big to brute
            // you could fallback to a greedy here, but for a "pure brute" we just bail
            cout << "Input too large for pure brute (n*m = " << N << ")\n";
            continue;
        }

        grid_.assign(N, 0);
        bestScore = -1;
        bestGrid.clear();

        dfs(0);

        // output the best found
        cout << bestScore << "\n";
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << bestGrid[i*m + j]
                     << (j+1==m? '\n' : ' ');
            }
        }
    }
    return 0;
}
