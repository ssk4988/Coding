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
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi par(n, -1), subsz(n);
    auto dfs = [&](int cur, int pre, auto &&dfs) -> void{
        subsz[cur] = 1;
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs(i, cur, dfs);
            subsz[cur] += subsz[i];
        }
    };
    dfs(0, -1, dfs);
    ll curans = 0, ans = 0;
    rep(i, 0, n){
        curans += subsz[i];
    }
    ans = max(ans, curans);
    // for(int i :)
    // curans += subsz[0];
    auto dfs2 = [&](int cur, int pre, auto&&dfs2) -> void{
        // curans -= subsz[cur];
        for(int i : adj[cur]){
            if(i == pre) continue;
            curans -= subsz[i];
            curans += n - subsz[i]; // subsz[par[i] = cur]
            ans = max(curans, ans);
            dfs2(i, cur, dfs2);
            curans -= n - subsz[i];
            curans += subsz[i];
        }
        // curans += subsz[cur];
    };
    dfs2(0, -1, dfs2);
    cout << ans << nL;

    
    return 0;
}