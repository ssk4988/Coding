#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

template<class F> struct centroid {
    vector<vi> adj;
    F f;
    vi sub_sz, par;
    centroid(const vector<vi>& a_adj, F a_f) : adj(a_adj), f(a_f), sub_sz(sz(adj), -1), par(sz(adj), -1) {
        rep(i, 0, sz(adj))
            if(sub_sz[i] == -1) dfs(i);
    }
    void calc_sz(int u, int p) {
        sub_sz[u] = 1;
        for(int v : adj[u])
            if(v != p)
                calc_sz(v, u), sub_sz[u] += sub_sz[v];
    }
    int dfs(int u) {
        calc_sz(u, -1);
        for(int p = -1, sz_root = sub_sz[u];;) {
            auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) { return v != p && 2 * sub_sz[v] > sz_root; });
            if(big_ch == end(adj[u])) break;
            p = u, u = *big_ch;
        }
        f(adj, u);
        for(int v : adj[u]) {
            iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
            adj[v].pop_back();
            par[dfs(v)] = u;
        }
        return u;
    }
};

vector<vi> treeJump(vi& P) {
    int on = 1, d = 1;
    while(on < sz(P)) on *= 2, d++;
    vector<vi> jmp(d, P);
    rep(i,1,d) rep(j, 0, sz(P))
        jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps) {
    rep(i, 0, sz(tbl))
        if(steps&(1<<i)) nod = tbl[i][nod];
    return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    a = jmp(tbl, a, depth[a] - depth[b]);
    if(a == b) return a;
    for(int i = sz(tbl); i--;) {
        int c = tbl[i][a], d = tbl[i][b];
        if(c != d) a = c, b = d;
    }
    return tbl[0][a];
}



int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    return 0;
}
