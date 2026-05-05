#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, totc; cin >> n >> m >> totc;
    vector dp(m+1, vii(totc+1, pii{0, 0}));
    dp[0][totc] = pii{0, 0};
    vl monh(n), mond(n);
    rep(i, 0, n) {
        cin >> monh[i] >> mond[i];
    }
    while(sz(monh) < m+5) {
        monh.push_back(monh[sz(monh) % n]);
        mond.push_back(mond[sz(mond) % n]);
    }
    n = sz(monh);
    vl h(m), d(m), c(m);
    rep(i, 0, m) {
        cin >> h[i] >> d[i] >> c[i];
        h[i]--;
        rep(cash, 0, totc+1) {
            auto [midx, mdmg] = dp[i][cash];
            dp[i+1][cash] = max(dp[i+1][cash], dp[i][cash]);
            if(cash < c[i]) continue;
            ll hits = mond[midx] == 0 ? 1e9 : h[i] / mond[midx];
            mdmg = min(monh[midx], hits * d[i] + mdmg);
            if(mdmg == monh[midx]) {
                midx++;
                mdmg = 0;
            }
            dp[i+1][cash-c[i]] = max(dp[i+1][cash-c[i]], {midx, mdmg});
        }
    }
    auto [midx, mdmg] = *max_element(all(dp.back()));
    ll totdmg = mdmg;
    rep(i, 0, midx) totdmg += monh[i];
    cout << mdmg << " " << totdmg << "\n";
    
    return 0;
}
