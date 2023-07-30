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

const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p/2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    vi comp(n, -1);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int nc = 0;
    auto dfs = [&](int cur, int c, auto &&dfs)->void{
        comp[cur] = c;
        for(int i : adj[cur]) if(comp[i] == -1) dfs(i, c, dfs);
    };
    rep(i, 0, n){
        if(comp[i] == -1){
            dfs(i, nc++, dfs);
        }
    }
    vi edgecnt(nc), nodecnt(nc);
    rep(i, 0, n){
        edgecnt[comp[i]] += sz(adj[i]);
        nodecnt[comp[i]]++;
    }
    ll ans = 1;
    rep(i, 0, nc){
        edgecnt[i] /= 2;
        ans = mod(ans * modpow(2, 1 + edgecnt[i] - nodecnt[i]));
    }
    cout << ans << nL;
    
    return 0;
}