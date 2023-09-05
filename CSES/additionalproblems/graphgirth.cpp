#include <bits/stdc++.h>
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
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int ans = INT_MAX;
    rep(i, 0, n){
        vi dist(n, INT_MAX), par(n, -1);
        dist[i] = 0;
        par[i] = i;
        queue<array<int, 3>> q;
        q.push({i, i, 0});
        while(!q.empty()){
            auto [k, pre, d] = q.front(); q.pop();
            if(par[k] != pre) ans = min(ans, d + dist[k]);
            else for(int nex : adj[k]){
                if(par[nex] == -1){
                    par[nex] = k;
                    dist[nex] = d + 1;
                }
                if(nex != pre) q.push({nex, k, d + 1});
            }

        }
    }
    if(ans == INT_MAX) ans = -1;
    cout << ans << nL;
    
    return 0;
}
