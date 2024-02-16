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
        int n, k; cin >> n >> k;
        vvi adj(n);
        rep(i, 0, k){
            vi a(n);
            rep(j, 0, n){
                cin >> a[j]; a[j]--;
            }
            rep(j, 1, n-1){
                adj[a[j]].pb(a[j+1]);
            }
        }
        vi state(n);
        auto dfs = [&](int u, auto &&dfs) -> bool {
            if(state[u] == 1) return true;
            if(state[u] == 2) return false;
            state[u] = 1;
            for(int v : adj[u]){
                if(dfs(v, dfs)) return true;
            }
            state[u] = 2;
            return false;
        };
        bool works = true;
        rep(i, 0, n){
            if(dfs(i, dfs)) works = false;
        }
        cout << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}