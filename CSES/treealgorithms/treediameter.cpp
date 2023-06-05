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
    int n;
    cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int farthest = -1, dist = -1;
    auto dfs = [&](int cur, int pre, int d, auto &&dfs)->void{
        if(d > dist){
            dist = d;
            farthest = cur;
        }
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs(i, cur, d + 1, dfs);
        }
    };
    dfs(0, -1, 0, dfs);
    int t1 = farthest;
    farthest = dist = -1;
    dfs(t1, -1, 0, dfs);
    cout << dist << nL;
    
    return 0;
}
