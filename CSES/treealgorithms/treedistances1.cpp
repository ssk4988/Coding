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
    int d1 = -1, d2 = -1, dist = -1;
    auto farthest = [&](int cur, int pre, int d, int &mod, auto &&farthest) -> void{
        if(d > dist){
            mod = cur;
            dist = d;
        }
        for(int i : adj[cur]){
            if(i == pre) continue;
            farthest(i, cur, d + 1, mod, farthest);
        }
    };
    farthest(0, -1, 0, d1, farthest);
    dist = -1;
    farthest(d1, -1, 0, d2, farthest);
    vi ondiam(n);
    auto dfsdiam = [&](int cur, int pre, auto && dfsdiam) -> bool{
        if(cur == d2){
            ondiam[cur] = true;
            return ondiam[cur];
        }
        for(int i : adj[cur]){
            if(i == pre) continue;
            if(dfsdiam(i, cur, dfsdiam)){
                ondiam[cur] = true;
                return true;
            }
        }
        return false;
    };
    // check 2 node graph, 3 node graph
    dfsdiam(d1, -1, dfsdiam);
    vi distfromdiam(n);
    auto dfsdist = [&](int cur, int pre, int d, auto &&dfsdist) -> void{
        distfromdiam[cur] = max(distfromdiam[cur], d);
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfsdist(i, cur, d + 1, dfsdist);
        }
    };
    dfsdist(d1, -1, 0, dfsdist);
    dfsdist(d2, -1, 0, dfsdist);
    rep(i, 0, n){
        cout << distfromdiam[i] << " ";
    }
    cout << nL;

    return 0;
}
