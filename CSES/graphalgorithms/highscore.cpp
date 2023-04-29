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
    vvi radj(n);
    rep(i, 0, m){
        int a, b; ll w; cin >> a >> b >> w;
        a--,b--;
        adj[a].pb({b, w});
        radj[b].pb(a);
    }
    ll BAD = -1'000'000'000'000'000LL;
    vl dist(n, BAD);
    dist[0] = 0;
    vi leads(n), visited(n);
    auto dfs = [&](int i, auto &&dfs)->void{
        // if(i == 2498){
        //     cout << "bruh";
        // }
        if(visited[i]) return;
        visited[i] = true;
        leads[i] = true;
        for(int j : radj[i]){
            dfs(j, dfs);
        }
    };
    dfs(n - 1, dfs);
    // rep(i, 0, n){
    //     if(leads[i]) cout << i << nL;
    // }
    rep(t, 0, m){
        rep(i, 0, n){
            if(dist[i] <= BAD) continue;
            for(pl &p : adj[i]){
                if(dist[i] + p.s > dist[p.f]){
                    dist[p.f] = dist[i] + p.s;
                }
            }
        }
        // cout << 5 << " ";
    }
    bool hascycle = false;
    rep(i, 0, n){
        if(dist[i] <= BAD) continue;
        for(pl &p : adj[i]){
            if(leads[p.f] && dist[i] + p.s > dist[p.f]){
                hascycle = true;
            }
        }
    }
    // rep(i, 0, n){
    //     if(dist[i] <= BAD) continue;
    //     for(pl &p : adj[i]){
    //         if(dist[i] + p.s > dist[p.f]){
    //             dist[p.f] = dist[i] + p.s;
    //         }
    //     }
    // }
    if(hascycle){
        cout << "-1\n";
    }
    else{
        cout << dist[n - 1] << nL;
    }
    
    
    return 0;
}