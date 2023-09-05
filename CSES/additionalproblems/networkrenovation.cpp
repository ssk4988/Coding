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
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi leaves;
    auto dfs = [&](int cur, int par, auto &&dfs)->void{
        if(sz(adj[cur]) == 1) leaves.pb(cur);
        for(int nex : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, dfs);
        }
    };
    dfs(0, -1, dfs);
    vpi edges;
    int n1 = sz(leaves) / 2 * 2;
    rep(i, 0, n1 / 2){
        edges.pb({1 + leaves[i], 1 + leaves[n1/2 + i]});
    }
    if(n1 < sz(leaves)){
        edges.pb({1 + leaves.front(), 1 + leaves.back()});
    }
    cout << sz(edges) << nL;
    for(auto [u, v] : edges) cout << u << " " << v << nL;
    
    return 0;
}
