#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for(int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if(a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};

const ll MOD = 998244353;

ll modpow(ll b, ll e) {
    ll ans = 1;
    for(; e; b = (b * b) % MOD, e /= 2) {
        if(e & 1) ans = (ans * b) % MOD;
    }
    return ans;
}

void solve() {
    int n, q; cin >> n >> q;
    vvi adj(n);
    vl deg(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        deg[u]++;
        deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vl score(n, 1);
    vi par(n, -1);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        score[u] = (score[u] * max(1LL, deg[u] - 1)) % MOD;
        par[u] = p;
        for(int v : adj[u]) if(v != p) {
            score[v] = score[u];
            dfs(v, u, dfs);
        }
    };
    dfs(0, -1, dfs);
    LCA lca(adj);
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--, b--;
        ll ans = deg[a];
        if(par[a] != -1) ans = (ans * score[par[a]]) % MOD;
        if(par[b] != -1) ans = (ans * score[par[b]]) % MOD;
        int l = lca.lca(a, b);
        ans = (ans * modpow(score[l], MOD-2)) % MOD;
        if(par[l] != -1) ans = (ans * modpow(score[par[l]], MOD-2)) % MOD;
        cout << ans << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    // int t;
    // cin >> t;
    // while (t--) 
    solve();

    return 0;
}
