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

using mat = array<array<ll, 2>, 2>;
const ll inf = 1e18;
mat init() {
    mat res;
    rep(i, 0, 2) rep(j, 0, 2) res[i][j] = -1;
    return res;
}
mat operator*(mat a, mat b) {
    mat res;
    if(a[0][0] == -1) return b;
    if(b[0][0] == -1) return a;
    rep(i, 0, 2) {
        rep(j, 0, 2) {
            res[i][j] = inf;
            rep(k, 0, 2) {
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl change(n);
    vector<vector<pair<int, ll>>> adj2(n+1);
    rep(i, 0, n) cin >> change[i], adj2[n].push_back({i, change[i]});
    vector<vector<tuple<int, ll, ll>>> adj(n);
    rep(i, 0, n-1) {
        int u, v; ll w1, w2; cin >> u >> v >> w1 >> w2; u--, v--;
        adj[u].push_back({v, w1, w2});
        adj[v].push_back({u, w1, w2});
        adj2[u].push_back({v, w1+w2});
        adj2[v].push_back({u, w1+w2});
    }
    using state = pair<ll, int>;
    priority_queue<state, vector<state>, greater<>> pq;
    vl dist(n+1, -1);
    pq.push({0, n});
    while(sz(pq)) {
        auto [d_u, u] = pq.top(); pq.pop();
        if(dist[u] != -1) continue;
        dist[u] = d_u;
        for(auto [v, w] : adj2[u]) {
            pq.push({d_u+w, v});
        }
    }
    rep(i, 0, n) change[i] = dist[i];

    vector<vector<mat>> matjmp(20, vector<mat>(n));
    vvi jmp(20, vi(n));
    vector<mat> ch(n, init());
    rep(i, 0, n) {
        ch[i][0][0] = ch[i][1][1] = 0;
        ch[i][0][1] = ch[i][1][0] = change[i];
    }
    vi dep(n);
    auto dfs = [&](int u, int par, auto &&dfs) -> void {
        rep(p, 0, sz(jmp)-1){
            jmp[p+1][u] = jmp[p][jmp[p][u]];
            matjmp[p+1][u] = matjmp[p][u] * matjmp[p][jmp[p][u]];
        }
        for(auto [v, w1, w2] : adj[u]) if(v != par) {
            jmp[0][v] = u;
            dep[v] = dep[u] + 1;
            matjmp[0][v] = ch[v] * mat{array<ll, 2>{w1, inf}, array<ll, 2>{inf, w2}};
            // matjmp[0][v][0][0] = min(w1, w2 + change[u] + change[v]);
            // matjmp[0][v][1][1] = min(w2, w1 + change[u] + change[v]);
            // matjmp[0][v][0][1] = min(w1 + change[u], change[v] + w2);
            // matjmp[0][v][1][0] = min(w2 + change[u], change[v] + w1);
            dfs(v, u, dfs);
        }
    };
    dfs(0, 0, dfs);
    rep(i, 0, n) {
        rep(p, 0, sz(jmp)) {
            if((1 << p) > dep[i]) break;
            assert(dep[i] == dep[jmp[p][i]] + (1 << p));
        }
    }
    int q; cin >> q;
    rep(i, 0, q) {
        int u, v; cin >> u >> v;
        u--, v--;
        int tu = u&1, tv = v&1;
        u/= 2, v /= 2;
        int l = u, r = v;
        mat lj = init(), rj = init();
        for(int p = sz(jmp)-1; p >= 0; p--) {
            if(dep[l] - (1 << p) >= dep[r]) {
                lj = lj * matjmp[p][l];
                l = jmp[p][l];
            }
            if(dep[r] - (1 << p) >= dep[l]) {
                rj = rj * matjmp[p][r];
                r = jmp[p][r];
            }
        }
        assert(dep[l] == dep[r]);
        if(l != r) {
            for(int p = sz(jmp)-1; p >= 0; p--) {
                if(jmp[p][l] != jmp[p][r]) {
                    lj = lj * matjmp[p][l];
                    l = jmp[p][l];
                    rj = rj * matjmp[p][r];
                    r = jmp[p][r];
                }
            }
            lj = lj * matjmp[0][l];
            rj = rj * matjmp[0][r];
            l = jmp[0][l], r = jmp[0][r];
        }
        {
            rj = rj * ch[r];
            mat revr;
            rep(a, 0, 2) {
                rep(b, 0, 2) {
                    revr[a][b] = rj[b][a];
                }
            }
            rj = revr;
        }
        mat res = lj * rj;
        ll ans = res[tu][tv];
        // rep(t, 0, 2) {
        //     ans = min(ans, lj[tu][t] + rj[tv][t]);
        // }
        cout << ans << "\n";
    }
    
    return 0;
}
