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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; ll k; cin >> n >> m >> k;
        vl h(n);
        rep(i, 0, n) cin >> h[i];
        vector<vector<pair<int, ll>>> adj(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--,b--;
            ll c = h[a] <= h[b] ? (h[b] - h[a]) : (k + h[b] - h[a]);
            adj[b].pb({a, c});
        }
        const ll BAD = -1;
        vl dp(n, BAD); // max dist to some ancestor
        auto solve = [&](int cur, auto &&solve)->void{
            if(dp[cur] != BAD) return;
            dp[cur] = 0;
            for(auto [par, w] : adj[cur]){
                solve(par, solve);
                dp[cur] = max(dp[cur], dp[par] + w);
            }
        };
        vpl ints;
        rep(i, 0, n){
            solve(i, solve);
            ll start = (((h[i] - dp[i]) % k + k) % k);
            ints.pb({start, start + dp[i]});
            // cout << "debug: " << i << " " << dp[i] << " " << start << " " << (start + dp[i]) << nL;
        }
        // sort(all(ints));
        map<ll, ll> buckets;
        for(auto [l, r] : ints){
            buckets[l] = max(buckets[l], r);
        }
        int v = sz(buckets);
        vl pre(v), suff(v);
        int i = 0;
        for(auto [l, r] : buckets){
            pre[i] = r;
            if(i) pre[i] = max(pre[i], pre[i - 1]);
            i++;
        }
        i = v - 1;
        for(auto it = buckets.rbegin(); it != buckets.rend(); it = next(it)){
            auto [l, r] = *it;
            suff[i] = r;
            if(i + 1 < v) suff[i] = max(suff[i], suff[i + 1]);
            i--;
        }
        // rep(i, 0, v){
        //     pre[i] = ints[i].s;
        // }
        // for(int i = v - 1; i >= 0; i--){
        //     suff[i] = ints[i].s;
        //     if(i + 1 < v) suff[i] = max(suff[i], suff[i + 1]);
        // }
        ll ans = LLONG_MAX;
        i = 0;
        for(auto [t, r] : buckets){
            ll pret = i ? (pre[i - 1] + k - t) : 0, sufft = suff[i] - t;
            ans = min(ans, max(pret, sufft));
            i++;
        }
        // rep(i, 0, v){
        //     ll t = ints[i].f;
        //     ll pret = i ? (pre[i] + k - t) : 0, sufft = suff[i] - t;
        //     ans = min(ans, max(pret, sufft));
        // }
        cout << ans << nL;

    }
    
    return 0;
}
