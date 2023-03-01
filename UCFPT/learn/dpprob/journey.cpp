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
    auto solve = [&](int cur, int par, auto &&solve) -> ld{
        if(adj[cur].size() == (par != -1 ? 1 : 0)) return 0;
        ld ans = 0;
        for(int a : adj[cur]){
            if(a == par) continue;
            ans += solve(a, cur, solve);
        }
        ans /= sz(adj[cur]) - (par != -1 ? 1 : 0);
        return ans + 1;
    };
    cout << solve(0, -1, solve) << nL;
    
    return 0;
}
