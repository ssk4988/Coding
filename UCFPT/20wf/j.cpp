#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;
const int oo = 1e9;
const int mult[] = {0, 1, 2, 2, 0};
// trans[curstate] = {send down, convert to}
const vii trans[] = {
    {
        {0, 0}
    },
    {
        {1, 3}, {0, 1}, {3, 1}
    },
    {
        {0, 2}, {1, 1}, {3, 2}, {2, 3}
    },
    {
        {0, 3}, {3, 3}
    },
    {
        {0, 4}, {4, 0}, {1, 1}, {2, 3}, {3, 2}
    }
};
using a5 = array<int, 5>;
using a55 = array<a5, 5>;

inline void filla55(a55 &a, const int v) {
    rep(i, 0, 5){
        a[i].fill(v);
    }
}
vector<vii> adj;
int n;
const int N = 100005;
a55 dp[N];
int go(int u, int p, int t1, int t2) {
    if (dp[u][t1][t2] != -1) return dp[u][t1][t2];
    // cout << "calc " << u << "," << p << " " << t1 << " " << t2 << endl;
    // vvi cur(5, vi(5, oo));
    a55 cur;
    filla55(cur, oo);
    cur[t1][t2] = 0;
    for(auto [v, w] : adj[u]){
        if(v == p) continue;
        rep(i, 0, 5){
            rep(j, 0, 5) go(v, u, i, j);
        }
        a55 newcur;
        filla55(newcur, oo);
        // vvi newcur(5, vi(5, oo));
        rep(s1, 0, 5){
            rep(s2, 0, 5) {
                for(auto [send1, conv1] : trans[s1]) {
                    for(auto [send2, conv2] : trans[s2]) {
                        if (mult[send1] + mult[send2] == 0) continue;
                        newcur[conv1][conv2] = min(newcur[conv1][conv2], 
                            cur[s1][s2] + w * (mult[send1] + mult[send2])
                                + dp[v][send1][send2]);
                    }
                }
            }
        }
        swap(newcur, cur);
    }
    int ans = oo;
    rep(i, 0, 5){
        rep(j, 0, 5){
            ans = min(ans, cur[i][j]);
        }
    }
    // cout << "calc " << u << "," << p << " " << t1 << " " << t2 << " = " << ans << endl;
    return dp[u][t1][t2] = ans;
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n;
    adj.resize(n);
    rep(i, 0, n-1){
        int u, v, w; cin >> u >> v >> w; u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    rep(i, 0, n){
        filla55(dp[i], -1);
    }

    // make sure that initial calls make sense
    int ans = go(0, -1, 4, 4);
    cout << ans << "\n";

    return 0;
}
