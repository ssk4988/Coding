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
        vvi adj(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--,b--;
            adj[b].pb(a);
        }
        vi dist(n, n + 1);
        dist[0] = 0;
        queue<int> q;q.push(0);
        vi inq(n);
        inq[0] = true;
        while(!q.empty()){
            int k = q.front(); q.pop();
            for(int i : adj[k]){
                if(inq[i]) continue;
                dist[i] = 1 + dist[k];
                inq[i] = true;
                q.push(i);
            }
        }
        int maxv = 0;
        rep(i, 0, n){
            maxv = max(dist[i], maxv);
        }
        if(maxv == n + 1){
            cout << "INFINITE\n";
            continue;
        }
        cout << "FINITE\n";
        vvi comp(maxv + 1);
        rep(i, 0, n) comp[dist[i]].pb(i);
        vi conf;
        for(int i = maxv; i >= 0; i--){
            rep(j, i, maxv + 1) conf.pb(j);
        }
        vi ans;
        for(int i : conf) for(int j : comp[i]) ans.pb(j + 1);
        cout << sz(ans) << nL;
        for(int i : ans) cout << i << " ";
        cout << nL;
    }
    
    return 0;
}
