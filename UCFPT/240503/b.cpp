#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ld = long double;

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, t, s; cin >> n >> t >> s;
    vvi g(n, vi(2)), b(n, vi(2));
    vector<vector<ld>> p(n, vector<ld>(2));
    rep(i, 0, n){
        rep(j, 0, 2){
            cin >> p[i][j] >> g[i][j] >> b[i][j];
            p[i][j] /= 100;
        }
    }
    ld inf = 1e15;
    cout << fixed << setprecision(10);
    auto test = [&](ld start)-> bool {
        map<pii, ld> dp;
        auto go = [&](int time, int stage, auto&& go) -> ld {
            if(dp.count({time, stage})) return dp[{time, stage}];
            ld &ans = dp[{time, stage}];
            ans = start;
            if(time >= t) return ans;
            if(stage == n){
                return ans = 0;
            }
            // cout << choice << "\n";
            ans = min({ans, 
                p[stage][0] * min(start, g[stage][0] + go(time + g[stage][0], stage + 1, go))
                + (1 - p[stage][0]) * min(start, b[stage][0] + go(time + b[stage][0], stage + 1, go)),
                p[stage][1] * min(start, g[stage][1] + go(time + g[stage][1], stage + 1, go))
                + (1 - p[stage][1]) * min(start, b[stage][1] + go(time + b[stage][1], stage + 1, go))
        });
            // cout << ans << " " << dp[{time, stage}] << "\n";
            // cout << mask << " " << start << " " << (s + start) << " " << ans << "\n";
            return ans;
        };
        ld res = s + go(s, 0, go);
        // cout << mask << " " << res << "\n";
        if(res <= start) return true;
        return false;
    };
    ld ans = 0;
    ld dif = inf;
    rep(i, 0, 200){
        if(!test(ans + dif)) ans += dif;
        dif /= 2;
    }
    cout << fixed << setprecision(12) << ans << "\n";
    return 0;
}
