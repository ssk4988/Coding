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

using bs = bitset<250005>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi subsz(n, 1);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        for(int v : adj[u]){
            if(v == p) continue;
            dfs(v, u, dfs);
            subsz[u] += subsz[v];
        }
    };
    dfs(0, -1, dfs);
    int cur = 0, pre = -1;
    while(true){
        bool fnd = false;
        // cout << cur << endl;
        for(int v : adj[cur]){
            if(v == pre) continue;
            if(2 * subsz[v] >= n){
                pre = cur;
                cur = v;
                fnd = true;
                break;
            }
        }
        if(!fnd) break;
    }
    subsz = vi(n, 1);
    dfs(cur, -1, dfs);
    bs sub;
    sub[0] = true;
    ll ans = 0;
    rep(i, 0, n) ans += subsz[i] - 1;
    for(int v : adj[cur]){
        sub |= sub << subsz[v];
    }
    ll best = 0;
    rep(i, 0, n+1){
        if(sub[i]) best = max(best, ll(i) * (n - 1 - i));
    }
    cout << (n - 1) << " " << (ans + best) << "\n";
    
    return 0;
}