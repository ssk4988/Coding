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
            int u, v; cin >>u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi col(n, -1);
        auto dfs = [&](int u, int c, auto &&dfs) -> bool {
            if(col[u] == c) return true;
            if(col[u] != -1){
                return false;
            }
            col[u] = c;
            for(int v : adj[u]){
                if(!dfs(v, 1 - col[u], dfs)) return false;
            }
            return true;
        };
        bool color2 = true;
        rep(i, 0, n){
            if(col[i] != -1) continue;
            if(!dfs(i, 0, dfs)){
                color2 = false;
            }
        }
        if(!color2){
            cout << "Alice" << endl;
            rep(i, 0, n){
                cout << 1 << " " << 2 << endl;
                int x, c; cin >> x >> c;
            }
            continue;
        }
        cout << "Bob" << endl;
        vvi cols(2);
        rep(i, 0, n) cols[col[i]].pb(i);
        rep(i, 0, n){
            int a, b; cin >> a >> b; a--, b--;
            set<int> used;
            used.insert(a);
            used.insert(b);
            bool done = false;
            rep(t, 0, 2){
                if(used.count(t) && sz(cols[t])){
                    cout << (cols[t].back()+1) << " " << (t+1) << endl;
                    cols[t].pop_back();
                    done = true;
                    break;
                }
            }
            if(!done){
                rep(t, 0, 2){
                    if(sz(cols[t])){
                        cout << (cols[t].back()+1) << " " << 3 << endl;
                        cols[t].pop_back();
                        done = true;
                        break;
                    }
                }
            }
        }
    }
    
    return 0;
}
