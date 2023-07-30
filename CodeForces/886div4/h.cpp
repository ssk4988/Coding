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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<vpl> adj(n);
        rep(i, 0, m){
            ll a, b, d; cin >> a >> b >> d;
            a--, b--;
            adj[a].pb({b, d});
            adj[b].pb({a, -d});
        }
        vl dist(n, LLONG_MAX);
        auto dfs = [&](int cur, ll d, auto &&dfs)->void{
            dist[cur] = d;
            for(auto [nex, w] : adj[cur]){
                if(dist[nex] == LLONG_MAX){
                    dfs(nex, d + w, dfs);
                }
            }
        };
        rep(i, 0, n){
            if(dist[i] == LLONG_MAX){
                dfs(i, 0, dfs);
            }
        }
        bool works = true;
        rep(i, 0, n){
            for(auto [j, w] : adj[i]){
                if(dist[j] - dist[i] != w) works = false;
            }
        }
        cout << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}