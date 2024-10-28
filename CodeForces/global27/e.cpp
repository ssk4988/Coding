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

vl genceils(ll y, ll lower, ll upper) {
    // for all reachable v such that ceil(y / x) = v, return smallest x that does so
    // nvm gen candidates
    vl res;
    if(upper - lower <= 1000) {
        for(ll x = lower; x <= min(y, upper); x++) res.pb(x);
        return res;
    }
    for(ll x = 1; true; x++) {
        ll z = (y + x - 1) / x;
        res.pb(x);
        res.pb(z);
        if(x >= z) break;
    }
    return res;
}

void solve() {
    ll inc_cost, atk_cost, health, k; cin >> inc_cost >> atk_cost >> health >> k;
    ll ans = 1e18;
    ll blocks = 0;
    // cout << sz(genceils(60900000)) << "\n";
    ll totcost = 0;
    while(true){
        ll d0 = blocks * (blocks+1) / 2 * k;
        ll tot0 = inc_cost * blocks * k + blocks * atk_cost;
        if(d0 >= health) {
            ans = min(ans, tot0);
            break;
        }
        if(tot0 > ans) break;
        ll left = health - d0;
        vl cands = genceils(left, k * blocks, k * blocks + k);
        totcost += sz(cands);
        for(auto cand : cands){
            ll rem = cand - k * blocks;
            if(rem < 0 || rem > k) continue;
            if(cand == 0) continue;
            ll req = (left + cand - 1) / cand;
            ll tot1 = rem * inc_cost + req * atk_cost;
            ans = min(ans, tot0 + tot1);
        }
        blocks++;
    }
    cout << ans << "\n";
    cerr << totcost << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    
    return 0;
}
