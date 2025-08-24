#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

#define f first
#define s second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    const int O = 2e6 + 10;
    const int W = 2 * O + 10;
    vector<vii> diffs(W);
    rep(i, 0, n) {
        rep(j, i+1, min(n, i + k+2)) {
            diffs[a[j]-a[i]+O].emplace_back(i, j);
        }
    }
    vii dp(n, {-1, -1});
    vi ans;
    rep(d, 0, W) {
        pii best{-1, -1};
        for(auto [i, j] : diffs[d]) {
            dp[i] = max(dp[i], pii{1, -1});
            dp[j] = max(dp[j], pii{dp[i].f+1, i});
            // cerr << "trans " << d-O << " i=" << i << " j=" << j << " " << dp[i].f << " " << dp[j].f << endl;
            best = max(best, pii{dp[j].f, j});
            best = max(best, pii{dp[i].f, i});
        }
        if(best.f == -1) continue;
        vi seq;
        seq.push_back(best.s);
        best = dp[best.s];
        while(best.s != -1) {
            seq.push_back(best.s);
            best = dp[best.s];
        }
        // cerr << "seq: ";
        // for(int v : seq) cerr << v << " ";
        // cerr << endl;
        if(sz(seq) > sz(ans)) ans = seq;
        for(auto [i, j] : diffs[d]) {
            dp[i] = {-1, -1};
            dp[j] = {-1, -1};
        }
    }
    if(sz(ans) + k < n) {
        cout << "-1\n";
        return 0;
    }
    reverse(all(ans));
    // for(int i : ans) cerr << i << " ";
    // cerr << endl;
    int p = 0;
    vi inv;
    rep(i, 0, n) {
        while(p < sz(ans) && ans[p] < i) p++;
        if(p < sz(ans) && ans[p] != i) inv.push_back(i);
    }
    cout << sz(inv) << "\n";
    for(int v : inv) {
        cout << v+1 << " ";
    }
    cout << "\n";

    
    return 0;
}
