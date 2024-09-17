#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const ll MOD = 1e9+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;

    vi to(2 * n - 1);
    rep(i, 0, n){
        rep(j, 0, n){
            to[i + j] += 1;
        }
    }
    vector<vl> totdp;
    rep(t, 0, 2) {
        vi cands;
        rep(i, 0, sz(to)){
            if((i & 1) == t) {
                cands.pb(to[i]);
            }
        }
        sort(all(cands));
        // reverse(all(cands));
        vi cnt, items;
        rep(i, 0, sz(cands)){
            if(i == 0 || cands[i] != cands[i-1]) {
                cnt.pb(0), items.pb(cands[i] - (i == 0 ? 0 : cands[i-1]));
            }
            cnt.back()++;
        }
        reverse(all(cnt));
        reverse(all(items));
        rep(i, 1, sz(cnt)){
            cnt[i] += cnt[i-1];
        }
        // cout << "t: " << t << endl;
        // rep(i, 0, sz(cnt)) {
        //     cout << i << " " << cnt[i] << " " << items[i] << endl;
        // }
        vector dp(sz(cnt)+1, vl(n+1, -1));
        auto go = [&](int layer, int used, auto &&go) -> ll {
            // cout << layer << " " << used << endl;
            auto &ans = dp[layer+1][used];
            if(ans != -1) return ans;
            if(layer == -1){
                return ans = (used == 0);
            }
            // if(items[layer] < used) return ans = 0;
            ans = 0;
            // use nothing
            ans += go(layer-1, used, go);
            // use 1
            if(used >= 1 && items[layer] >= 1)
            {
                int free = cnt[layer] - (used-1);
                if(free >= 1) (ans += free * items[layer] * go(layer-1, used-1, go)) %= MOD;
            }
            // use 2
            if(used >= 2 && items[layer] >= 2) {
                int free = cnt[layer] - (used-2);
                if(free >= 2) (ans += (free * (free-1)) % MOD * go(layer-1, used-2, go)) %= MOD;
            }
            ans %= MOD;
            return ans;
        };
        totdp.push_back({});
        rep(i, 0, n+1) {
            ll v = go(sz(cnt)-1, i, go);
            totdp.back().pb(v);
            // cout << i << "," << v << endl;
        }
    }
    ll ans = 0;
    rep(i, 0, n+1){
        rep(j, 0, n+1) {
            if(i < sz(totdp[0]) && j < sz(totdp[1]) && i + j == k) {
                (ans += (totdp[0][i] * totdp[1][j] % MOD)) %= MOD;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
