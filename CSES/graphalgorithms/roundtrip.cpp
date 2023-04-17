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
    int n ,m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0 ,m){
        int a,b; cin >> a >> b;a--,b--;
        adj[a].pb(b);adj[b].pb(a);
    }
    vi visited(n),path;
    set<int> paths;
    auto dfs = [&](int i, int pre, auto &&dfs)->bool{
        visited[i] = true;
        for(int j : adj[i]){
            if(j == pre) continue;
            if(paths.count(j)){
                path.pb(j);
                return true;
            }
            if(!visited[j]){
                path.pb(j);
                paths.insert(j);
                if(dfs(j, i, dfs)) return true;
                path.pop_back();
                paths.erase(j);
            }
        }
        return false;
    };
    rep(i, 0, n){
        path.pb(i);
        paths.insert(i);
        if(dfs(i, -1, dfs)){
            break;
        }
        paths.clear();
        path.clear();
    }
    bool works = path.size() && paths.count(path.back());
    if(works){
        int st = 0;
        while(path[st] != path.back()) st++;
        cout << (sz(path) - st) << nL;
        rep(i, st, sz(path)){
            cout << (1 + path[i]) << " ";
        }
        cout << nL;
    }
    else cout << "IMPOSSIBLE\n";
    
    return 0;
}
