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
    vector<vpl> adj(n);
    rep(i, 0, m){
        int a, b; ll c; cin >> a >> b >> c;
        a--,b--;
        adj[a].pb({b, c});
    }
    vi path;
    bool works = false;
    vi visited(n);
    auto dfs = [&](int cur, ll d, auto &&dfs)->bool{
        path.pb(cur);
        visited[cur] = true;
        if(path.size() > 1 && path.front() == path.back()){
            return d < 0;
        }
        for(pl &p : adj[cur]){
            if((!visited[p.s] || p.s == path.front()) && d + p.s <= 0){
                if(dfs(p.f, d + p.s, dfs)) return true;
            }
        }
        // visited[cur] = false;
        path.pop_back();
        return false;
    };
    rep(i, 0, n){
        if(dfs(i, 0, dfs)){
            works = true;
            break;
        }
    }
    if(works){
        cout << "YES\n";
        for(int i : path) cout << (i+1) << " ";
        cout << nL;
    }
    else{
        cout << "NO\n";
    }
    
    return 0;
}
