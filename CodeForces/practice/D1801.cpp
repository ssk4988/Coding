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

using pp = pair<pl, pi>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; ll p; cin >> n >> m >> p;
        vector<vpl> adj(n);
        vl ws(n);
        rep(i, 0, n) cin >> ws[i];
        rep(i, 0, m){
            int a, b, c; cin >> a >> b >> c;a--,b--;
            adj[a].pb({b, c});
        }
        priority_queue<pp, vector<pp>, greater<pp>> pq;
        pq.push({{0, p}, {0, 0}});
        vector<vpl> dp(n, vpl(n, {LLONG_MAX, LLONG_MAX}));
        dp[0][0] = {0, p};
        vvi visited(n, vi(n));
        while(!pq.empty()){
            auto [val, state] = pq.top(); pq.pop();
            auto [cur, best] = state;
            if(visited[cur][best]) continue;
            visited[cur][best] = true;
            for(auto [nex, w] : adj[cur]){
                int newmax = ws[nex] > ws[best] ? nex : best;
                if(visited[nex][newmax]) continue;
                auto [cnt, money] = val;
                if(money < w){
                    ll newamt = (w - money + ws[best] - 1) / ws[best];
                    cnt += newamt;
                    money += newamt * ws[best];
                }
                money -= w;
                pl val2 = {cnt, money};
                if(val2 < dp[nex][newmax]){
                    dp[nex][newmax] = val2;
                    pq.push({dp[nex][newmax], {nex, newmax}});
                }
            }
        }
        ll ans = LLONG_MAX;
        rep(i, 0, n){
            ans = min(dp[n - 1][i].f, ans);
        }
        if(ans == LLONG_MAX) cout << "-1\n";
        else cout << ans << nL;
    }
    
    return 0;
}
