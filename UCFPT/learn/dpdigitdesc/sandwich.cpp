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

// 1043
// 3210 - digit indexes
const int D = 14;
const int MAX_OVERLAP = 1000500;

vl p10{1};
tuple<vi, vl, vl> get_digs(ll x) {
    vi res;
    while(sz(res) < D) {
        res.pb(x % 10);
        x /= 10;
    }
    vl pref(sz(res)), suff(sz(res));
    rep(i, 0, sz(res)) {
        if(i) pref[i] = pref[i-1];
        pref[i] += res[i] * p10[i];
    }
    for(int i = sz(res)-1; i >= 0; i--) {
        if(i+1 < sz(res)) suff[i] = suff[i+1] * 10;
        suff[i] += res[i];
    }
    return {res, pref, suff};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(i, 0, 16) p10.pb(p10.back() * 10);
    vi canonical(MAX_OVERLAP, 1);
    rep(overlap, 1, MAX_OVERLAP) {
        auto [digs, pref, suff] = get_digs(overlap);
        int prefidx = 0;
        for(int suffidx = sz(suff)-1; suffidx > 0; suffidx--) {
            while(prefidx < sz(pref) && pref[prefidx] < suff[suffidx]) prefidx++;
            if(prefidx < sz(pref) && pref[prefidx] == suff[suffidx] && pref[prefidx] != 0) {
                canonical[overlap] = false;
            }
        }
    }
    rep(cn, 0, nc) {
        ll lim; cin >> lim; lim++; // count nums < lim
        auto [limdig, limpref, limsuff] = get_digs(lim);
        vector dp(D, vector(2, vector(D, vl(2, -1))));
        auto go = [&](int dig, bool suffdiverge, int stopdig, bool prefdiverge, auto &go) -> ll {
            ll &ans = dp[dig][suffdiverge][stopdig][prefdiverge];
            if(ans != -1) return ans;
            if(dig == stopdig) {
                return ans = suffdiverge || prefdiverge;
            }
            ans = 0;
            rep(d, 0, 10) {
                if(!suffdiverge && d > limdig[dig]) continue;
                ans += go(dig-1, suffdiverge || d < limdig[dig], stopdig, prefdiverge, go);
            }
            return ans;
        };
        int overlaplen = 0;
        ll ans = 0;
        for(ll overlap = 1; overlap < MAX_OVERLAP; overlap++) {
            if(overlap == p10[overlaplen]) overlaplen++;
            if(!canonical[overlap]) continue;
            rep(between, 0, D) {
                ll start = overlap * p10[overlaplen + between] + overlap;
                if(start >= lim) break;
                bool prefdiverge = overlap < limpref[overlaplen-1];
                bool suffdiverge = overlap < limsuff[overlaplen + between];
                ans += go(overlaplen + between - 1, suffdiverge, overlaplen-1, prefdiverge, go);
            }
        }
        cout << "Number #" << (cn+1) << ": There are " << ans << " sandwich numbers that meet our criteria.\n";
    }
    
    return 0;
}
