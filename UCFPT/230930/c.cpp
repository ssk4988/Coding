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

vi topsort(vvi &adj){
    vector<bool> vis(sz(adj));
    vi ts;
    auto dfs = [&](int cur, auto && dfs)->void{
        if(vis[cur]) return;
        for(int nex : adj[cur]) dfs(nex, dfs);
        vis[cur] = true;
        ts.pb(cur);
    };
    for(int i = 0; i < sz(adj); i++){
        dfs(i, dfs);
    }
    reverse(all(ts));
    return ts;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj1(n), adj2(n);
    map<int, map<int, vi>> ed;
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--, b--;
        adj1[a].pb(b);
        ed[a][b].pb(i);
        int t; cin >> t;
        if(t) swap(a, b);
        adj2[a].pb(b);
    }
    vi ts1 = topsort(adj1), ts2 = topsort(adj2);
    vi rev1(n), rev2(n);
    rep(i, 0, n){
        rev1[ts1[i]] = i;
        rev2[ts2[i]] = i;
    }
    bool possible = true;
    vi ans;
    rep(t, 0, n){
        rep(i, 0, n - 1){
            if(rev2[ts1[i]] > rev2[ts1[i + 1]]){
                if (sz(ed[ts1[i]][ts1[i + 1]]) > 1){
                    possible = false;
                }
                else if(sz(ed[ts1[i]][ts1[i + 1]]) == 1){
                    ans.pb(ed[ts1[i]][ts1[i + 1]][0] + 1);
                }
                swap(ts1[i], ts1[i + 1]);
            }
        }
    }
    if(!possible) cout << "-1\n";
    else{
        cout << sz(ans) << nL;
        for(int i : ans) cout << i << " ";
        cout << nL;
    }
    
    return 0;
}
