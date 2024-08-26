#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

void solve() {
    int n; cin >> n;
    vvi a(n), nxt(n), use(n);
    rep(i, 0, n){
        int k; cin >> k;
        rep(j, 0, k){
            int v; cin >> v;
            a[i].push_back(v);
        }
        sort(all(a[i]));
    }
    auto contain = [&](vi &v, int k) -> bool {
        auto it = lower_bound(all(v), k);
        return it != v.end() && *it == k;
    };
    auto get_idx = [&](vi &v, int k) -> int {
        auto it = lower_bound(all(v), k);
        return it - v.begin();
    };
    rep(i, 0, n){
        for(int j : a[i]){
            if(!contain(a[0], j) || !contain(a.back(), j)){
                use[i].push_back(j);
            }
        }
    }
    for(int i = n-1; i >= 0; i--) {
        nxt[i].resize(sz(a[i]));
        rep(j, 0, sz(a[i])){
            if(i + 1 == n){
                nxt[i][j] = n;
                continue;
            }
            int v = a[i][j];
            nxt[i][j] = !contain(a[i+1], v) ? i+1 : nxt[i+1][get_idx(a[i+1], v)];
        }
    }
    vector<pair<int, int>> dp(n+1, {-1, -1});
    for(int i = n-1; i >= 0; i--) {
        dp[i] = {i, -1};
        rep(j, 0, sz(nxt[i])){
            dp[i] = max(dp[i], {dp[nxt[i][j]].first, j});
        }
    }
    // rep(i, 0, n){
    //     cout << i << ": ";
    //     rep(j, 0, sz(nxt[i])){
    //         cout << a[i][j] <<" ";
    //     }
    //     cout << "\n";
    // }
    // rep(i, 0, n){
    //     cout << i << ": ";
    //     rep(j, 0, sz(nxt[i])){
    //         cout << nxt[i][j] <<" ";
    //     }
    //     cout << "\n";
    // }
    // rep(i, 0, n){
    //     cout << i << ": " << dp[i].first << " " << dp[i].second << "\n";
    // }
    bool works = false;
    vi ans;
    rep(i, 0, sz(nxt[0])){
        if(nxt[0][i] == n) {
            ans.assign(n, a[0][i]);
            works = true;
            break;
        }
        if(contain(a.back(), a[0][i])){
            int last = dp[nxt[0][i]].first;
            if(!contain(a[last], a[0][i])) continue;
            works = true;
            rep(j, 0, nxt[0][i]) ans.push_back(a[0][i]);
            int cur = nxt[0][i];
            while(cur != last) {
                auto [nxtcur, take] = dp[cur];
                while(sz(ans) < nxtcur) ans.push_back(a[cur][take]);
                cur = nxtcur;
            }
            while(sz(ans) != n) ans.push_back(a[0][i]);
            break;
        }
        int last = dp[nxt[0][i]].first;
        if(sz(use[last]) == 0) continue;
        works = true;
        rep(j, 0, nxt[0][i]) ans.push_back(a[0][i]);
        int cur = nxt[0][i];
        while(cur != last) {
            auto [nxtcur, take] = dp[cur];
            while(sz(ans) < nxtcur) ans.push_back(a[cur][take]);
            cur = nxtcur;
        }
        while(sz(ans) != n) ans.push_back(use[last][0]);
        break;
    }
    if(!works) cout << -1 << "\n";
    else {
        for(int i : ans) cout << i << " ";
        cout << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // int t; cin >> t; while(t--)
    solve();

    return 0;
}
