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
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi height(n);
    vector<vpi> branches(n);
    auto longestExcluding = [&](int cur, int exc)->pi{
        if(sz(branches[cur]) && branches[cur][0].f != exc) return branches[cur][0];
        else if(sz(branches[cur]) > 1) return branches[cur][1];
        return {0, -1};
    };
    vector<unordered_map<int, int>> dep(n);
    auto dfs = [&](int cur, int par, auto &&dfs)->void{
        height[cur] = 0;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, dfs);
            height[cur] = max(height[cur], 1 + height[nex]);
            branches[cur].pb({1 + height[nex], nex});
        }
    };
    dfs(0, -1, dfs);
    auto dfs2 = [&](int cur, int par, auto &&dfs2)->void{
        dep[cur][par] = height[cur];
        if(par != -1){
            pi exc = longestExcluding(par, cur);
            branches[cur].pb({1 + exc.f, par});
        }
        sort(all(branches[cur]));
        reverse(all(branches[cur]));
        for(int i : adj[cur]){
            if(i == par) continue;
            dfs2(i, cur, dfs2);
        }
    };
    dfs2(0, -1, dfs2);
    
    return 0;
}
