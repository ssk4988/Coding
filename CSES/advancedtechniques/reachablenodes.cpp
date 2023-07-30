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

const int maxn = 50002;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
    }
    vector<bitset<maxn>> ans(n);
    auto dfs = [&](int cur, auto &&dfs)->bitset<maxn>{
        if(ans[cur].any()) return ans[cur];
        ans[cur].set(cur);
        for(int nex : adj[cur]) ans[cur] |= dfs(nex, dfs);
        return ans[cur];
    };
    rep(i, 0, n) cout << dfs(i, dfs).count() << " ";
    cout << nL;
    
    return 0;
}