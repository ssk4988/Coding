#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

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
    auto diam = [&](int u, int p, auto &&diam) -> vi {
        vi best;
        for(int v : adj[u]) if (v != p) {
            vi cur = diam(v, u, diam);
            if(sz(cur) > sz(best)) swap(cur, best);
        }
        best.pb(u);
        return best;
    };
    vi di = diam(0, -1, diam);
    di = diam(di[0], -1, diam);
    if(sz(di) <= 3) {
        cout << "NO\n";
        return 0;
    }
    int start = di[1];
    int lastadj = di[2];
    adj[start].erase(find(all(adj[start]), lastadj));
    adj[start].pb(lastadj);
    vi ans;
    auto dfs = [&](int u, int p, auto &&dfs)->void {
        ans.pb(u);
        for(int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
        }
    };
    dfs(start, -1, dfs);
    cout << "YES\n";
    for(int i : ans) cout << i+1 << " ";
    cout << "\n";
    
    return 0;
}
