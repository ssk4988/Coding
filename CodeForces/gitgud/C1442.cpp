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

const ll MOD = 998244353;
ll mod(ll k){
    return k % MOD;
}
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

using a3 = array<ll, 3>;
using a4 = array<ll, 4>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<set<int>> adj(n), radj(n);
    int LIM = 20;
    // vl pw2;
    // pw2.pb(1);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].insert(b); radj[b].insert(a);
    }
    // rep(i, 0, 2 * max(n, m)){
    //     pw2.pb(mod(pw2.back() * 2 + 1));
    // }
    vector<vl> dist(n, vl(LIM, 1e18));
    dist[0][0] = 0;
    priority_queue<a3, vector<a3>, greater<a3>> pq;
    pq.push({0, 0, 0});
    while(!pq.empty()){
        auto [d, u, b] = pq.top(); pq.pop();
        if(d > dist[u][b]) continue;
        auto &adjlist = (b % 2 ? radj : adj)[u];
        for(auto v : adjlist){
            if(dist[v][b] > d + 1){
                dist[v][b] = d + 1;
                pq.push({dist[v][b], v, b});
            }
        }
        if(b + 1 < LIM && dist[u][b+1] > d + (1LL << b)){
            dist[u][b+1] = d + (1LL << b);
            pq.push({dist[u][b+1], u, b+1});
        }
    }
    if(dist[n-1][LIM-1] != 1e18){
        ll ans = dist[n-1][LIM-1];
        rep(i, 0, LIM) ans = min(ans, dist[n-1][i]);
        cout << mod(ans) << "\n";
        return 0;
    }
    // cout << "got here" << endl;
    priority_queue<a4, vector<a4>, greater<a4>> pq2;
    vector<vector<pl>> finaldist(n, vpl(2, {1e18, 1e18}));
    finaldist[0][0] = {0, 0};
    pq2.push({0, 0, 0, 0});
    while(!pq2.empty()){
        auto [inv, d, u, p] = pq2.top(); pq2.pop();
        if(pl{inv, d} > finaldist[u][p]) continue;
        for(auto v : (p ? radj : adj)[u]){
            if(finaldist[v][p] > pl{inv, d + 1}){
                finaldist[v][p] = {inv, d + 1};
                pq2.push({inv, d+1, v, p});
            }
        }
        if(finaldist[u][p ^ 1] > pl{inv + 1, d}){
            finaldist[u][p ^ 1] = {inv + 1, d};
            pq2.push({inv+1, d, u, p ^ 1});
        }
    }
    auto [inv, d] = min(finaldist[n-1][0], finaldist[n-1][1]);
    ll ans = modpow(2, inv);
    ans = mod(ans + MOD - 1);
    ans = mod(ans + d);
    cout << ans << "\n";
    return 0;
}
