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
    vi visited(n), parity(n);
    auto dfs = [&](int i, int p, auto &&dfs)->void{
        visited[i] = true;
        parity[i] = p;
        for(int j : adj[i]){
            if(!visited[j]){
                dfs(j, !p, dfs);
            }
        }
    };
    rep(i,0,n){
        if(!visited[i])
            dfs(i,0,dfs);

    }
    bool works = true;
    rep(i, 0, n){
        for(int j : adj[i]){
            if(parity[i] == parity[j]){
                works = false;
            }
        }
    }
    if(works){
        rep(i,0,n){
            cout << (1 + parity[i]) << " ";
        }
        cout << nL;
    }
    else cout << "IMPOSSIBLE\n";
    
    return 0;
}
