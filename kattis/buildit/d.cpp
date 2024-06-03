#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("trapv")

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
    vl primes;
    rep(i, 2, 1000){
        bool div = false;
        rep(j, 2, i){
            if(i % j == 0){
                div = true;
                break;
            }
        }
        if(!div){
            primes.pb(i);
        }
    }
    vvi adj(n);
    vl x(n, -1);
    x[0] = 1;
    vi subsz(n, 1), depth(n);
    vi par(n, -1);
    rep(i, 0 ,n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    auto dfs = [&](int u, int p, auto &&dfs)->void {
        par[u] = p;
        if(p != -1){
            adj[u].erase(find(all(adj[u]), p));
        }
        for(int v : adj[u]) {
            dfs(v, u, dfs);
        }
    };
    dfs(0, -1, dfs);
    auto filldepth = [&](int u, auto &&filldepth) -> void {
        for(int v : adj[u]){
            depth[v] = depth[u] + 1;
            filldepth(v, filldepth);
        }
    };
    filldepth(0, filldepth);
    priority_queue<pii> pq;
    rep(i, 0, n){
        pq.push({depth[i], i});
    }
    rep(times, 0, n){
        pii best = {-1, -1};
        rep(i, 0, n){
            if(x[i] != -1) continue;
            best = max(best, {depth[i], i});
        }
        if(best.f == -1) break;
        auto [d, i] = best;
        ll p = primes[times];
        auto go = [&](int u, auto &&go) -> ll {
            if(x[u] != -1) return x[u];
            ll res = go(par[u], go);
            depth[u] = 0;
            filldepth(u, filldepth);
            return x[u] = p * res;
        };
        go(i, go);
    }
    rep(i, 0, n) cout << x[i] << " ";
    cout << "\n";
    
    return 0;
}
