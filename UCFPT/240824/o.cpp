#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int REQ = 9;
using mat = array<array<ll, REQ>, REQ>;

mat operator*(mat a, mat b) {
    mat res;
    rep(i, 0, REQ){
        rep(j, 0, REQ){
            res[i][j] = 0;
            rep(k, 0, REQ){
                res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}


template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

template<class T>
struct RMQMX {
    vector<vector<T>> jmp;
    RMQMX(const vector<T> &V) : jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = max(jmp[k-1][j], jmp[k-1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret, depth;
    RMQ<int> rmq;

    LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for(int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            depth[y] = depth[v] + 1;
            dfs(C, y, v);
        }
    }
    int lca(int a, int b) {
        if(a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

void solve() {
    // check N=1?????????
    vi ns(2); int q;
    cin >> ns[0] >> ns[1] >> q;
    vector<vvi> adj(2);
    vector<LCA> lcas;
    vvi diams, ondiams, diamdist, diamnode;
    vector<vii> deepest;
    vector<RMQMX<pii>> rmqs;
    rep(t, 0, 2){
        int n = ns[t];
        adj[t].resize(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[t][u].push_back(v);
            adj[t][v].push_back(u);
        }
        lcas.emplace_back(adj[t]);
        auto getdiam = [&](int u, int p, auto &&getdiam) -> vi {
            vi best;
            for(int v : adj[t][u]){
                if(v == p) continue;
                auto cur = getdiam(v, u, getdiam);
                if(sz(cur) > sz(best)) swap(cur, best);
            }
            best.push_back(u);
            return best;
        };
        vi diam = getdiam(0, -1, getdiam);
        diam = getdiam(diam[0], -1, getdiam);
        diams.push_back(diam);
        ondiams.emplace_back(n, -1);
        diamnode.emplace_back(n);
        diamdist.emplace_back(n);
        deepest.emplace_back(sz(diam), pii{-1, -1});
        // if(n == 1) continue;
        // cout << n << endl;
        rep(i, 0, sz(diam)){
            ondiams[t][diam[i]] = i;
        }
        auto dfs = [&](int u, int p, int idx, pii&best, auto &&dfs) -> void {
            best = max(best, {diamdist[t][u], u});
            diamnode[t][u] = idx;
            for(int v : adj[t][u]){
                if(v == p || ondiams[t][u] != -1) continue;
                diamdist[t][v] = 1 + diamdist[t][u];
                dfs(v, u, idx, best, dfs);
            }
        };
        rep(i, 0, sz(diam)) {
            diamnode[t][diam[i]] = i;
            deepest[t][i] = {0, diam[i]};
            for(int j : adj[t][diam[i]]){
                if(ondiams[t][j] == -1){
                    diamdist[t][j] = 1;
                    dfs(j, diam[i], i, deepest[t][i], dfs);
                }
            }
        }
        rmqs.emplace_back(deepest[t]);
    }
    #define f first
    #define s second
    rep(_, 0, q){
        pii a, b; cin >> a.f >> b.f >> a.s >> b.s;
        a.f--, a.s--, b.f--, b.s--;
        if(ns[0] == 1 || ns[1] == 1) {
            if(a.f == a.s && b.f == b.s) cout << 0 << "\n";
            else cout << -1 << "\n";
            continue;
        }
        int d1 = lcas[0].dist(a.f, a.s), d2 = lcas[1].dist(b.f, b.s);
        int t1 = d1 < d2 ? 0 : 1;
        int t2 = 1 - t1;
        if(d1 >= d2) {
            swap(d1, d2);
            swap(a, b);
        }
        if(d1 == d2){
            cout << (d1 > 0) << "\n";
            continue;
        }
        if(abs(d1 - d2) % 2 != 0){
            cout << -1 << "\n";
            continue;
        }
        int l = diamnode[t1][a.f], r = diamnode[t1][a.s];
        if(l > r) swap(l, r);
        vi nodes = {a.f, a.s, diams[t1][0], diams[t1].back()};
        // cout << l << " " << r << endl;
        if(l + 1 < r) nodes.push_back(rmqs[t1].query(l+1, r).second);
        if(l) nodes.push_back(rmqs[t1].query(0, l).second);
        if(r + 1 < sz(diams[t1])) nodes.push_back(rmqs[t1].query(r+1, sz(diams[t1])).second);
        nodes.push_back(rmqs[t1].query(l, l+1).second);
        nodes.push_back(rmqs[t1].query(r, r+1).second);
        nodes.resize(REQ);
        mat dist;
        rep(i, 0, REQ){
            rep(j, 0, REQ){
                dist[i][j] = lcas[t1].dist(nodes[i], nodes[j]);
            }
        }
        vector<mat> pws = {dist};
        while(pws.back()[0][1] < d2){
            pws.push_back(pws.back() * pws.back());
        }
        pws.pop_back();
        mat cur(pws.back());
        ll ans = 1LL << sz(pws);
        ll cnt = 1LL << (sz(pws)-1);
        for(int i = sz(pws)-1; i >= 0; i--) {
            mat tmp = cur * pws[i];
            if(tmp[0][1] < d2) {
                swap(tmp, cur);
                cnt += 1LL << i;
            }
        }
        ans = min(ans, cnt+1);
        cout << ans << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // int t; cin >> t; while(t--)
    solve();

    return 0;
}
