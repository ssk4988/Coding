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
    int n, m; cin >> n >> m;
    vpl a(n), b(m);
    rep(i, 0, n) cin >> a[i].f, a[i].s = i;
    rep(i, 0, m) cin >> b[i].f, b[i].s = i;
    sort(all(a));
    sort(all(b));
    vector<vector<optional<pi>>> nxt(m, vector<optional<pi>>(n+1, nullopt));
    rep(i, 0, m){
        rep(j, 0, n){
            int use = (b[i].f + a[j].f - 1) / a[j].f;
            if(use + j <= n) nxt[i][j] = {j+ use, j};
        }
        // rep(j, 0, n){
        //     if(nxt[i][j]) cout << b[i].f << " " << j << " " << a[j].f << " " << *nxt[i][j] << "\n";
        // }
        for(int j=n-2; j >= 0; j--) {
            if(nxt[i][j+1] && (!nxt[i][j] || nxt[i][j]->f > nxt[i][j+1]->f)) nxt[i][j] = nxt[i][j+1];
        }
    }
    vector<optional<pair<int, pi>>> dp(1 << m);
    dp[0] = {0, pi{-1, -1}};
    rep(mask, 0, 1 << m){
        if(!dp[mask]) continue;
        auto [idx, bb] = *dp[mask];
        rep(i, 0, m){
            if((mask >> i) & 1) continue;
            if(!nxt[i][idx]) continue;
            pair<int, pi> val = {nxt[i][idx]->f, pi{mask, i}};
            if(!dp[mask ^ (1 << i)] || *dp[mask ^ (1 << i)] > val) {
                dp[mask ^ (1 << i)] = val;
            }
        }
    }
    if(!dp[(1 << m)-1]) {
        cout <<"NO\n";
        return 0;
    }
    vector<vi> ans(m);
    int mask = (1 << m)-1;
    while(mask) {
        auto [idx, bb] = *dp[mask];
        auto [pmask, take] = bb;
        auto [pidx, _] = *dp[pmask];
        rep(i, nxt[take][pidx]->s, idx)
            ans[b[take].s].pb(a[i].s);
        mask = pmask;
    }
    cout << "YES\n";
    rep(i, 0, m){
        cout << sz(ans[i]) << " ";
        for(int j : ans[i]) cout << j+1 << " ";
        cout << "\n";
    }
    
    return 0;
}
