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
    vvi adj(n), radj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        radj[b].pb(a);
    }
    vi visited(n), reaches(n), reachedby(n);
    auto dfs = [&](int cur, auto &&dfs)->void{
        if(reaches[cur])return;
        reaches[cur] = true;
        for(int i : adj[cur]) dfs(i, dfs);
    };
    dfs(0, dfs);
    auto dfs2 = [&](int cur, auto &&dfs2)->void{
        if(reachedby[cur])return;
        reachedby[cur] = true;
        for(int i : radj[cur]) dfs2(i, dfs2);
    };
    dfs2(0, dfs2);
    pi ans = {-1, -1};
    rep(i, 0, n){
        if(!reachedby[i]){
            ans = {i, 0};
            break;
        }
        if(!reaches[i]){
            ans = {0, i};
            break;
        }
    }
    if(ans.f == -1){
        cout << "YES\n";
    }else{
        cout << "NO\n";
        cout << (ans.f + 1) << " " << (ans.s + 1) << nL;
    }
    
    
    return 0;
}
