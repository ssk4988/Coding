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
    int n, k; cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<multiset<int>> lfs(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        int bestc = -1;
        for(int v : adj[u]) {
            if(v == p) continue;
            dfs(v, u, dfs);
            if(bestc == -1 || sz(lfs[v]) > sz(lfs[bestc])) bestc = v;
        }
        if(bestc == -1){
            lfs[u].insert(1);
            return;
        }
        else {
            swap(lfs[u], lfs[bestc]);
        }
        for(int v : adj[u]){
            if(v == p) continue;
            for(int x : lfs[v]) lfs[u].insert(x);
            lfs[v].clear();
        }
        int tp = *lfs[u].rbegin();
        lfs[u].erase(prev(lfs[u].end()));
        lfs[u].insert(tp+1);
    };
    dfs(0, -1, dfs);
    vi res{all(lfs[0])};
    // rep(i, 0, sz(res)) cout << res[i] << " ";
    // cout << endl;
    int used = 0;
    reverse(all(res));
    int leaves = min(sz(res), k);
    rep(i, 0, min(sz(res), k)) {
        used += res[i];
    }
    auto score = [&](ll r) -> ll {
        int b = min(n/2, n - used);
        return (n - r - b) * (r - b);
    };
    ll s = score(leaves);
    while(leaves < k && score(leaves+1) > score(leaves)) leaves++;
    cout << score(leaves) << endl;
    
    return 0;
}
