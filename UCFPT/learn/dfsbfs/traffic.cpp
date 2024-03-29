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
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n){
            int d; cin >> d;
            rep(j, 0, d){
                int b; cin >> b; b--;
                adj[i].pb(b);
                adj[b].pb(i);
            }
        }
        int c; cin >> c;
        cout << "City #" << (cn + 1) << "\n";
        rep(i, 0, c){
            int k; cin >> k; k--;
            vi vis(n);
            auto dfs = [&](int u, auto &&dfs) -> void {
                if(vis[u]) return;
                if(u == k) return;
                vis[u] = true;
                for(int v : adj[u]){
                    dfs(v, dfs);
                }
            };
            int cnt = 0;
            rep(i, 0, n){
                if(i == k || vis[i]) continue;
                cnt++;
                dfs(i, dfs);
            }
            cout << (cnt <= 1 ? "no" : "yes") << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}
