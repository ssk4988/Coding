#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
#define sz(x) (int)x.size()

struct RollbackUF {
    vi e; vector<array<int, 3>> st;
    vi idxs;
    RollbackUF(int n) : e(n, -1) {
        idxs = vi(n);
        iota(idxs.begin(), idxs.end(), 0);
    }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return sz(st); }
    void rollback(int t) {
        for (int i = time(); i --> t;) { 
            e[st[i][0]] = st[i][1];
            idxs[st[i][0]] = st[i][2];
        }
        st.resize(t);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a], idxs[a]});
        st.push_back({b, e[b], idxs[b]});
        e[a] += e[b]; e[b] = a;
        idxs[a] = max(idxs[a], idxs[b]);
        return true;
    }
    int idxMax(int x) {
        x = find(x);
        return idxs[x];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<string> board(n);
    for (int i = 0; i < n; i++) cin >> board[i];
    vector<RollbackUF> dsuX(n, RollbackUF(m+1));
    int filled = 0;  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = board[i][j];
            if (c == '.') dsuX[i].join(j, j+1);
            else filled++;
        }
    } 
    vector<vi> dp(n, vi(m));
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            char c = board[i][j];
            if (c == '.') continue;
            dp[i][j] = 1;
            if (i+1 < n && j+1 < m) {
                dp[i][j] += min({dp[i+1][j], dp[i][j+1], dp[i+1][j+1]});
            }
        }
    }
    vi pp;
    int d = min(n, m);
    vi prime(d+1, 1);
    for (int i = 2; i <= d; i++) {
        if (prime[i]) {
            for(int j = 2 * i; j <= d; j += i) prime[j] = 0;
            int p = 1;
            while (p*i <= d) {
                p *= i;
                pp.push_back(p);
            }
        }
    }
    vector<int> resetTimers(n);
    for (int i = 0; i < n; i++) resetTimers[i] = dsuX[i].time();

    // cout << "DP" << endl;
    // for (int i = 0; i < n; i++) { 
    //     for (int j = 0; j < m; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int ans = 1;
    for (int p : pp) {
        if(filled % (p*p)) continue;
        // cout << p << endl;
        // cout << "IDX MAX" << endl;
        // for (int i = 0; i < n; i++) { 
        //     for (int j = 0; j < m; j++) {
        //         cout << dsuX[i].idxMax(j) << " ";
        //     }
        //     cout << endl;
        // }
        bool pWorks = true;
        for (int i = 0; i < n && pWorks; i++) {
            int j = dsuX[i].idxMax(0);
            while (j < m) {
                // if (p == 3) {
                //     cout << i << " " << j << endl;
                // }
                if (dp[i][j] < p) {
                    pWorks = false;
                    break;
                }

                for (int k = i; k < i+p; k++) {
                    dsuX[k].join(j, j+p);
                }
                j = dsuX[i].idxMax(j);
            }
        }
        if (pWorks) {
            ans = lcm(ans, p);
        }
        for (int i = 0; i < n; i++) dsuX[i].rollback(resetTimers[i]);
    }
    cout << ans << endl;
}
