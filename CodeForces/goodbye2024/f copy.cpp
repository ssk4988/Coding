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

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<map<int, ll>> freq(n);
    vector<map<ll, vi>> freqfreq(n);
    vl ext(n);
    rep(i, 0, n){
        rep(j, 0, m){
            int v; cin >> v; if(v == -1) ext[i]++;
            else freq[i][v]++;
        }
        for(auto [c, v] : freq[i]){
            freqfreq[i][v].pb(c);
        }
        // freqfreq[i][0].pb(-1);
    }

    vl natural(n);
    rep(i, 0, n-1){
        for(auto [c, v] : freq[i]) {
            if(freq[i+1].count(c)) natural[i] += freq[i][c] * freq[i+1][c];
        }
    }
    vl pref(n);
    rep(i, 1, n) {
        pref[i] = pref[i-1] + ext[i] * ext[i-1];
    }
    vll dp(n); // t, v
    auto norm = [&](int k, int t) -> void {
        dp[k].s -= pref[dp[k].f];
        dp[k].s += pref[t];
        dp[k].f = t;
    };
    rep(i, 1, n) {

        vi keys;
        for(auto [c, val] : freq[i+1]) {
            keys.pb(c);
        }
        for(auto [c, val] : freq[i]) {
            keys.pb(c);
        }
        map<int, ll> fdp;
        for(auto key : keys) {
            int c1 = freq[i+1].count(key) ? key : -1;
            int c = freq[i].count(key) ? key : -1;
            if(c1 == -1 && c == -1) continue;
            norm(key, i-1);
            ll &res = fdp[freq[i-1].count(key) ? freq[i-1][key] : 0];
            res = max(res, dp[key]);
        }
        map<int, ll> upd;
        for(auto )
            // auto [t, v] = dp[key];
            // dp[key] = max()
            // dp[i+1][c1] = max(dp[i+1][c], dp[i][c] + (freq[i][c] + ext[i]) * (freq[i+1][c1] + ext[i+1]) - freq[i][c] * freq[i+1][c1] + natural[i]);
        }

    }
    rep(i, 0, n-1){
        // use c_i+1 is present in row i, c_i is present in row i+1
        vll pdp;
        for(auto &[frq, cs] : freqfreq[i+1]) {
            pdp.pb({frq, 0});
            for(auto c : cs) pdp.back().s = max(pdp.back().s, dp[i][freq[i].count(c) ? c : -1]);
        }
        for(auto &[frq, cs] : freqfreq[i]) {
            ll mx = 0;
            for(auto &[frq1, pdpv] : pdp) {
                mx = max(mx, ext[i] * frq1 + ext[i+1] * frq + pdpv);
            }
            for(auto c : cs) {
                dp[i+1][freq[i+1].count(c) ? c : -1] = max(dp[i+1][freq[i+1].count(c) ? c : -1], mx + natural[i]);
            }
        }
        // c == c1
        vi keys;
        for(auto [c, val] : freq[i+1]) {
            keys.pb(c);
        }
        for(auto [c, val] : freq[i]) {
            keys.pb(c);
        }
        for(auto key : keys) {
            int c1 = freq[i+1].count(key) ? key : -1;
            int c = freq[i].count(key) ? key : -1;
            dp[i+1][c1] = max(dp[i+1][c], dp[i][c] + (freq[i][c] + ext[i]) * (freq[i+1][c1] + ext[i+1]) - freq[i][c] * freq[i+1][c1] + natural[i]);
        }
        for(auto [c1, val] : freq[i+1]) {
            // c1 == c
            int c = freq[i].count(c1) : c1 : c;
            dp[i+1][c1] = max(dp[i+1][c1], dp[i][c] + (freq[i][c] + ext[i]) * (freq[i+1][c1] + ext[i+1]) - freq[i][c] * freq[i+1][c1] + natural[i]);
            
        }
    }
    ll ans = 0;
    rep(c, 0, k) ans = max(ans, dp[n-1][c]);
    // rep(i, 0, n) ans += natural[i];
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}


// vll p1;
        // for(auto &[frq, cs] : freqfreq[i]){
        //     p1.pb({frq, 0});
        //     for(auto c : cs) p1.back().s = max(p1.back().s, dp[i][c]);

        // }
        // for(auto &[frq, cs] : freqfreq[i+1]){
        //     ll mx = 0;
        //     for(auto [frq1, v1] : p1) {
        //         mx = max(mx, ext[i+1] * frq1 + ext[i] * frq + v1 + natural[i]);
        //     }
        //     for(auto c : cs) dp[i+1][c] = mx;
        // }
