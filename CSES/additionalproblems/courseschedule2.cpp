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
    vvi par(n);
    vector<set<int>> ods(n);
    vi outdegree(n);
    rep(i, 0, m){
        int a, b;
        cin >> a >> b;
        a--;b--;
        adj[a].pb(b);
        par[b].pb(a);
    }
    vi ans;
    // vector<pair<vi, int>> ps;
    rep(i, 0, n){
        // sort(all(adj[i]));
        // ps.pb({adj[i], i});
        outdegree[i] = adj[i].size();
        ods[adj[i].size()].insert(i);
    }
    while(ans.size() < n){
        int k = *(ods[0].rbegin());
        ods[0].erase(ods[0].find(k));
        ans.pb(k + 1);
        for(int i : par[k]){
            ods[outdegree[i]].erase(ods[outdegree[i]].find(i));
            outdegree[i]--;
            ods[outdegree[i]].insert(i);
        }
    }
    reverse(all(ans));
    rep(i, 0, n - 1){
        cout << ans[i] << " ";
    }
    cout << ans[n - 1] << nL;

    
    return 0;
}