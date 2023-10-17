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
    vi indeg(n);
    vpi ed;
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        indeg[b]++;
        adj[a].pb(b);
        ed.pb({a, b});
    }
    vi ts;
    queue<int> q;
    rep(i, 0, n) if(indeg[i] == 0) q.push(i);
    while(!q.empty()){
        int k = q.front(); q.pop();
        ts.push_back(k);
        for(int j : adj[k]){
            indeg[j]--;
            if(indeg[j] == 0) q.push(j);
        }
    }
    vi id(n);
    rep(i, 0, n){
        id[ts[i]] = i;
    }
    // rep(i, 0, n) cout << i << " " << ts[i] << nL;
    rep(i, 0, m){
        auto [a, b] = ed[i];
        a = id[a], b = id[b];
        if((a / 1600) != (b / 1600)){
            cout << "R\n";
        }
        else if((a / 40) != (b / 40)){
            cout << "B\n";
        }
        else{
            cout << "G\n";
        }
    }

    return 0;
}
