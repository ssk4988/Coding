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

map<vi, int> rl;
int dfshash(int cur, int par, vvi &adj)
{
    vi cs;
    for (int nex : adj[cur])
    {
        if (nex == par)
            continue;
        cs.pb(dfshash(nex, cur, adj));
    }
    sort(all(cs));
    if (rl.count(cs) == 0)
        rl[cs] = sz(rl);
    return rl[cs];
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
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
        vi subsz(n, 1);
        auto dfssub = [&](int cur, int par, auto &&dfssub)->void{
            for(int nex : adj[cur]){
                if(nex == par)continue;
                dfssub(nex, cur, dfssub);
                subsz[cur] += subsz[nex];
            }
        };
        dfssub(0, -1, dfssub);
        vi centroids;
        auto findcentroid = [&](int cur, int par, auto &&findcentroid)->void{
            int biggest = 0;
            for(int nex : adj[cur]){
                if(nex == par) continue;
                biggest = max(biggest, subsz[nex]);
            }
            if(biggest <= n/2 && n - subsz[cur] <= n / 2){
                centroids.pb(cur);
            }
            for(int nex : adj[cur]){
                if(nex == par) continue;
                if(subsz[nex] >= n/2){
                    findcentroid(nex, cur, findcentroid);
                }
            }
        };
        findcentroid(0, -1, findcentroid);
        vi hash1;
        for(int i : centroids){
            hash1.pb(dfshash(i, -1, adj));
        }
        adj = vvi(n);
        subsz = vi(n, 1);
        centroids.clear();
        rep(i, 0, n - 1)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        dfssub(0, -1, dfssub);
        findcentroid(0, -1, findcentroid);
        vi hash2;
        for(int i : centroids){
            hash2.pb(dfshash(i, -1, adj));
        }
        bool works = false;
        for(int i : hash1){
            for(int j : hash2){
                if(i == j) works = true;
            }
        }
        cout << (works ? "YES" : "NO") << nL;
    }

    return 0;
}
