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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve() {
    int n, root; cin >> n >> root; root--;
    vi ord;
    vvi adj(n);
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n-1){
        int u, v; cin >>u>>v; u--, v--; adj[u].pb(v); adj[v].pb(u);
    }
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        if(p != -1){
            auto it = find(all(adj[u]), p);
            adj[u].erase(it);
        }
        for(int v : adj[u]){
            dfs(v, u, dfs);
        }
        ord.pb(u);
    };
    dfs(root, -1, dfs);
    ll ans = 1e18;
    rep(pref, 0, n) {
        for(int p : {0, 1}){
            ll lo = -3;
            for(ll dif = 1LL << 40; dif; dif /= 2){
                ll cur = (lo + dif) * 2 + p;
                if(cur < 0){
                    lo = lo + dif;
                    continue;
                }
                vll res(n);
                bool works = true;
                for(int u : ord){
                    auto &[ops, left] = res[u];
                    ll cops = cur + (u < pref);
                    for(int v : adj[u]){
                        auto &[ops1, left1] = res[v];
                        ops += ops1;
                        left += left1;
                    }
                    left += a[u];
                    ll rem = min(cops, left);
                    cops -= rem;
                    // ops += cops;
                    left -= rem;
                    left += cops&1;
                    // if(cops % 2 == 1) works = false;
                }
                if(works && res[root].second == 0 && res[root].first % 2 == 0){
                    // works
                } else lo += dif;
            }
            lo++;
            ll cur = lo * 2 + p;
            if(cur > (1LL << 40)) continue;
            ll ops = cur * n + pref;
            // cout << "pref " << pref << " p " << p << " cur " << cur << " ops " << ops << "\n";
            ans = min(ans, ops);
        }
    }
    if(ans > 1e17){
        cout << "-1\n";
        return;
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();    
    }
    
    return 0;
}
