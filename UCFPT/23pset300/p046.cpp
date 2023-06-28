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
    vi depths(n, -1), heights(n, -1);
    auto dfs = [&](int cur, auto &&dfs)->void{
        if(depths[cur] != -1) return;
        depths[cur] = 0;
        for(int i : adj[cur]){
            dfs(i, dfs);
            depths[cur] = max(depths[cur], 1 + depths[i]);
        }
    };
    int ans = n;
    rep(i, 0, n){
        if(sz(radj[i]) == 0){
            dfs(i, dfs);
        }
    }
    swap(radj, adj);
    swap(heights, depths);
    rep(i, 0, n){
        if(sz(radj[i]) == 0){
            dfs(i, dfs);
        }
    }
    swap(radj, adj);
    // swap(heights, depths);
    int maxlen = 0;
    rep(i, 0, n) maxlen = max(maxlen, depths[i] + heights[i]);
    ans = maxlen;
    vi cnt(maxlen + 1);
    rep(i, 0, n){
        if(depths[i] + heights[i] == maxlen) cnt[depths[i]]++;
    }
    rep(i, 0, n){
        if(depths[i] + heights[i] == maxlen && cnt[depths[i]] == 1){
            vi ds;
            for(int j : adj[i]){
                ds.pb(heights[j] + 1);
            }
            sort(all(ds));
            reverse(all(ds));
            ans = min(ans, depths[i] + (sz(ds) >= 2 ? ds[1] : 0));
        }
    }
    cout << ans << nL;


    
    return 0;
}
