#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Suffix Automaton with vector<pair<char,int>> transitions
struct State {
    int len, link;
    vector<pair<char,int>> next;
};

static const int MAXM = 400000 + 5;
static const int LOGM = 19;
static int sp[LOGM][MAXM];
static int lg2[MAXM];

vector<State> st;
int sz, last;

void sa_init(int maxlen) {
    st.clear();
    st.reserve(2 * maxlen);
    st.push_back({0, -1, {}});
    sz = 1;
    last = 0;
}

int sa_get_next(int v, char c) {
    for (auto &pr : st[v].next)
        if (pr.first == c) return pr.second;
    return -1;
}

void sa_set_next(int v, char c, int u) {
    st[v].next.emplace_back(c, u);
}

void sa_extend(char cc) {
    int c = cc;
    int cur = sz++;
    st.push_back({st[last].len + 1, 0, {}});
    int p = last;
    while (p != -1 && sa_get_next(p, c) == -1) {
        sa_set_next(p, c, cur);
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = sa_get_next(p, c);
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st.push_back(st[q]);
            st[clone].len = st[p].len + 1;
            // link will be set below
            while (p != -1 && sa_get_next(p, c) == q) {
                for (auto &pr : st[p].next) {
                    if (pr.first == c && pr.second == q) {
                        pr.second = clone;
                        break;
                    }
                }
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute logs
    lg2[1] = 0;
    for (int i = 2; i < MAXM; i++) lg2[i] = lg2[i>>1] + 1;

    int T;
    cin >> T;
    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        string a, b;
        a.reserve(n);
        b.reserve(m);
        cin >> a >> b;
        // Build SA on reversed a
        sa_init(n);
        for (int i = n-1; i >= 0; i--) sa_extend(a[i]);

        // Match on reversed b
        vector<int> match_rev(m);
        int v = 0, l = 0;
        for (int i = m-1; i >= 0; i--) {
            char c = b[i];
            int nxt = sa_get_next(v, c);
            if (nxt != -1) {
                v = nxt;
                l++;
            } else {
                while (v != -1 && sa_get_next(v, c) == -1) {
                    v = st[v].link;
                }
                if (v == -1) {
                    v = 0;
                    l = 0;
                } else {
                    l = st[v].len + 1;
                    v = sa_get_next(v, c);
                }
            }
            match_rev[i] = l;
        }
        // Build match_start: for original b positions
        vector<int> match(m);
        for (int i = 0; i < m; i++) match[i] = match_rev[m-1-i];

        // Build sparse table for RMQ min on match[]
        for (int i = 0; i < m; i++) sp[0][i] = match[i];
        for (int k = 1; (1<<k) <= m; k++) {
            int len = 1<<k;
            int half = len>>1;
            for (int i = 0; i + len <= m; i++) {
                sp[k][i] = min(sp[k-1][i], sp[k-1][i+half]);
            }
        }

        auto range_min = [&](int L, int R) {
            int len = R - L + 1;
            int k = lg2[len];
            int half = 1<<k;
            return min(sp[k][L], sp[k][R-half+1]);
        };

        // Process queries
        while (q--) {
            int lq, rq;
            cin >> lq >> rq;
            int L = rq - lq + 1;
            int lo = 1, hi = L, ans = 0;
            int base = lq - 1;
            int r0 = rq - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                int end = r0 - mid + 1;
                if (range_min(base, end) >= mid) {
                    ans = mid;
                    lo = mid + 1;
                } else hi = mid - 1;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}