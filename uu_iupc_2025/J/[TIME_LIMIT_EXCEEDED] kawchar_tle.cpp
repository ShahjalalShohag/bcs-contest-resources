#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr ll BIG = 1000000000LL;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> A(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }

        int cnt = 0, maxNeg = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] == -1) cnt++;
            else cnt = 0;
            maxNeg = max(maxNeg, cnt);
        }
        ll bestPureNeg = maxNeg * BIG;

        vector<int> knownPos;
        vector<ll>  knownVal;
        for (int i = 0; i < n; i++) {
            if (A[i] != -1) {
                knownPos.push_back(i);
                knownVal.push_back(A[i]);
            }
        }
        int m = (int)knownPos.size();
        if (m == 0) {
            cout << bestPureNeg << "\n";
            continue;
        }

        vector<ll> prefixKnown(m + 1, 0LL);
        for (int i = 0; i < m; i++) {
            prefixKnown[i+1] = prefixKnown[i] + knownVal[i];
        }
        
        vector<ll> gapWeighted(m, 0LL);
        for (int i = 1; i < m; i++) {
            ll gapLen = (ll)(knownPos[i] - knownPos[i-1] - 1);
            gapWeighted[i] = gapWeighted[i-1] + gapLen * knownVal[i];
        }

        ll bestWithKnowns = LLONG_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                if (j > i && knownVal[j] < knownVal[j-1]) {
                    break;
                }

                ll sumKnown = prefixKnown[j+1] - prefixKnown[i];
                ll sumGapsInside = gapWeighted[j] - gapWeighted[i];

                ll leftStart = (i == 0 ? 0LL : knownPos[i-1] + 1LL);
                ll leftGapLen = knownPos[i] - leftStart;
                if (leftGapLen < 0) leftGapLen = 0;
                ll fillLeft = leftGapLen * knownVal[i];

                ll rightEnd = (j == m-1 ? (ll)(n - 1) : (ll)knownPos[j+1] - 1LL);
                ll rightGapLen = rightEnd - (ll)knownPos[j];
                if (rightGapLen < 0) rightGapLen = 0;
                ll fillRight = rightGapLen * BIG;

                ll total = sumKnown + sumGapsInside + fillLeft + fillRight;
                bestWithKnowns = max(bestWithKnowns, total);
            }
        }

        ll answer = max(bestWithKnowns, bestPureNeg);
        cout << answer << "\n";
    }

    return 0;
}
