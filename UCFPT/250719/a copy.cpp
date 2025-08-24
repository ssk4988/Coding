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
    auto cmp = [&](int i, int j) { return a[i] < a[j]; };
    vvi prvs(n);
    vi v;
    using a3 = array<int, 3>;
    using a4 = array<int, 4>;
    vector<vector<a3>> dp(n);
    vi p(n);
    a3 best{-1, -1, -1}; // len, i, ij
    rep(i, 0, n) {
        if(i) {
            auto it = lower_bound(all(v), a[i-1], cmp);
            v.insert(it, i-1);
        }
        if(i-(k+1) >= 0) {
            auto it = lower_bound(all(v), i-(k+1));
            v.erase(it);
        }
        rep(idx, 0, sz(v)) {
            int j = v[idx];
            int diff = a[j] - a[i];
            a3 trans{2, j, -1};
            while(p[j] < sz(dp[j]) && a[dp[j][p[j]][1]] - a[j] < a[j] - a[i]) {
                p[j]++;
            }
            if(p[j] < sz(dp[j]) && a[dp[j][p[j]][1]] - a[j] == a[j] - a[i]) {
                trans[0] = max(trans[0], dp[j][p[j]][0]+1);
            }
            cerr << "try " << j << " to " << i << " " << trans[0] << " " << trans[1] << " " << trans[2] << endl;
            if(sz(dp[i]) && a[j] - a[i] == a[dp[i].back()[1]] - a[i]) {
                dp[i].back() = max(dp[i].back(), trans);
            } else dp[i].push_back(trans);
            best = max(best, a3{dp[i].back()[0], i, sz(dp[i])-1});
        }
        rep(j, 0, sz(dp[i])) {
            cerr << i << " " << j << " " << dp[i][j][0] << " " << dp[i][j][1] << " " << dp[i][j][2] << endl;
        }
    }
    if(best[0] + k < n) {
        cout << "-1\n";
        return 0;
    }
    vi seq;
    while(true) {
        auto [cnt, i, j] = best;
        seq.push_back(i);
        if(j == -1) break;
        best = dp[i][j];
    }
    for(int x : seq) cout << x << " ";
    cout << "\n";
    
    return 0;
}
