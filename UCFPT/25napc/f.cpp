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

const ll mod = 1e9+7;
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = sz(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod,
      inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}

ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; e /= 2, (b *= b) %= mod)
        if(e&1) (res *= b) %= mod;
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, r; cin >> n >> r;
    r--;
    vi tin(n), tout(n);
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int T = 0;
    vi par(n, -1);
    vl multsub(n, 1);
    vi subsz(n, 1);
    grow(n+5);
    vi depth(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        tin[u] = T++;
        for(int v : adj[u]) if(v != p) {
            depth[v] = depth[u] + 1;
            par[v] = u;
            dfs(v, u, dfs);
            subsz[u] += subsz[v];
            (multsub[u] *= multsub[v]) %= mod;
        }
        (multsub[u] *= subsz[u]) %= mod;
        tout[u] = T;
    };
    dfs(r, -1, dfs);
    vl reord(n);
    rep(i, 0, n) {
        reord[i] = t[subsz[i]].fact * modpow(multsub[i], mod-2) % mod;
        // cerr << i << " par " << par[i] << " reord " << reord[i] << " " << subsz[i] << " " << multsub[i] << endl;
    }
    auto anc = [&](int anc, int dec) { return tin[anc] <= tin[dec] && tout[dec] <= tout[anc]; };
    ll ans = 0;
    rep(a, 0, n) {
        rep(b, 0, n) {
            if(a == b) continue;
            if(anc(a, b) && par[b] != a) {
                continue;
            }
            if(anc(b, a)) continue;
            // cerr << "trying a=" << a << " b=" << b << endl;
            ll pref = 1;
            int lca = r;
            ll otherinter = 1, othersz = 0, otherreord = 1;
            rep(u, 0, n) {
                // find nodes whose parent are internal ancestors of a or b and arent above a or b
                int p = par[u];
                if(anc(u, a) && anc(u, b) && tin[u] > tin[lca]) lca = u;
                if(anc(u, a) || anc(u, b)) continue;
                if(p == a || p == b) continue;
                if(!(anc(p, a) || anc(p, b))) continue;
                othersz += subsz[u];
                (otherinter *= C(othersz, subsz[u])) %= mod;
                (otherreord *= reord[u]) %= mod;
            }
            int apath = a == lca ? 0 : depth[a] - depth[lca]-1;
            int bpath = b == lca ? 0 : depth[b] - depth[lca]-1;
            (pref *= C(apath + bpath, apath)) %= mod;
            // ways to order prefix * ways to interleave others together * ways to reorder other subtrees
            // * ways to interleave sub[a], sub[b] together * ways to reorder sub[a], sub[b]
            // brute force where a,b go in sequence of others
            int subtot = 0;
            ll subinter = 1, subreord = 1;
            if(par[b] == a) {
                for(int v : adj[a]) if(v != par[a] && v != b) {
                    subtot += subsz[v];
                    (subinter *= C(subtot, subsz[v])) %= mod;
                    (subreord *= reord[v]) %= mod;
                }
                for(int v : adj[b]) if(v != par[b]) {
                    subtot += subsz[v];
                    (subinter *= C(subtot, subsz[v])) %= mod;
                    (subreord *= reord[v]) %= mod;
                }
            } else {
                subtot = subsz[a] + subsz[b] - 2;
                subinter = C(subtot, subsz[a]-1);
                subreord = reord[a] * reord[b] % mod;
            }
            // index of ab in others
            ll ways = 0;
            ll base = pref % mod * otherinter % mod * otherreord % mod * subinter % mod * subreord % mod;
            ll interothersub = 0;
            rep(ab, 0, othersz+1) {
                int suff = othersz - ab;
                (interothersub += C(suff+subtot, suff)) %= mod;
            }
            ways = (interothersub * base) % mod;
            // cerr << ways << endl;
            (ans += abs(a-b) * ways) %= mod;
        }
    }
    cout << ans << "\n";
    return 0;
}

// 1,0
// 0,2x
// 2,3x
// 1,0
// 0,3
// 3,2x
// 1,2
// 2,0x
// 0,3
