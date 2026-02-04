#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using ld = long double;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, r, m; cin >> n >> r >> m;
    vi ts(m), ds(m);
    vector<ld> ps(m);
    rep(i, 0, m) {
        cin >> ts[i] >> ps[i] >> ds[i];
    }
    ld final_ts = n - ts.back();
    for(int i = m-1; i > 0; i--) ts[i] -= ts[i-1];
    int tot_slack = r-n-1;
    // cerr << "tot_slack " << tot_slack << endl;
    ld lo = 0, hi = 1e18;
    rep(_, 0, 100) {
        ld mid = (lo+hi)/2;
        // expected time to break record with current state
        vector dp(m+1, vector<ld>(tot_slack+1, -1));
        auto go = [&](int i, int slack, auto &&go) -> ld {
            if(slack < 0) return 1e18;
            if(i >= m) return final_ts;
            auto &ans = dp[i][slack];
            if(ans != -1) return ans;
            ld keep = ts[i] + ps[i] * go(i+1, slack, go);
            ld fail = (1-ps[i]) * min(mid, ds[i] + go(i+1, slack - ds[i], go));
            ans = keep + fail;
            return ans;
        };
        ld ans = go(0, tot_slack, go);
        // cerr << "mid=" << mid << " ans=" << ans << endl;
        if(ans > mid) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(10) << lo << "\n";

    return 0;
}
