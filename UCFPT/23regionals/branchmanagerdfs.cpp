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
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep(i, 0, n) sort(all(adj[i]));
    vi qs(m);
    rep(i, 0, m){
        cin >> qs[i]; qs[i]--;
    }
    int ans = 0;
    unordered_set<int> path;
    auto dfs = [&](int cur, int par, auto &&dfs)-> void {
        path.insert(cur);
        while(ans < m && path.count(qs[ans])) ans++;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, dfs);
        }
        path.erase(cur);
    };
    dfs(0, 0, dfs);
    cout << ans << nL;
    

    
    return 0;
}
