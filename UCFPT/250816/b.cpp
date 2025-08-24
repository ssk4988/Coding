#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct SplayTree {
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        ll self = 0, path = 0;
        ll sub = 0, vir = 0;
        bool flip = 0;
    };
    vector<Node> T;

    SplayTree(int n): T(n+1) {}

    void push(int x) {
        if(!x || !T[x].flip) return;
        int l = T[x].ch[0], r = T[x].ch[1];

        T[l].flip ^= 1, T[r].flip ^= 1;
        swap(T[x].ch[0], T[x].ch[1]);
        T[x].flip = 0;
    }

    void pull(int x) {
        int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r);
        T[x].path = max({T[l].path, T[x].self, T[r].path});
        T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
    }

    void set(int x, int d, int y) {
        T[x].ch[d] = y; T[y].p = x; pull(x);
    }

    void splay(int x) {
        auto dir = [&](int x) {
            int p = T[x].p; if(!p) return -1;
            return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
        };
        auto rotate = [&](int x) {
            int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
            set(y, dx, T[x].ch[!dx]);
            set(x, !dx, y);
            if(~dy) set(z, dy, x);
            T[x].p = z;
        };

        for(push(x); ~dir(x); ) {
            int y = T[x].p, z = T[y].p;
            push(z); push(y); push(x);
            int dx = dir(x), dy = dir(y);
            if(~dy) rotate(dx != dy ? x : y);
            rotate(x);
        }
    }
};

struct LinkCut : SplayTree {
    LinkCut(int n): SplayTree(n) {}

    int access(int x) {
        int u = x, v = 0;
        for(; u; v = u, u = T[u].p) {
            splay(u);
            int &ov = T[u].ch[1];
            T[u].vir += T[ov].sub;
            T[u].vir -= T[v].sub;
            ov = v; pull(u);
        }
        return splay(x), v;
    }

    void reroot(int x) {
        access(x); T[x].flip ^= 1; push(x);
    }

    void Link(int u, int v) {
        reroot(u); access(v);
        T[v].vir += T[u].sub;
        T[u].p = v; pull(v);
    }

    void Cut (int u, int v) {
        reroot(u); access(v);
        T[v].ch[0] = T[u].p = 0; pull(v);
    }

    int LCA(int u, int v) {
        if(u == v) return u;
        access(u); int ret = access(v);
        return T[u].p ? ret : 0;
    }

    ll Subtree(int u, int v) {
        reroot(v); access(u); return T[u].vir + T[u].self;
    }

    ll Path(int u, int v) {
        reroot(u); access(v); return T[v].path;
    }

    void Update(int u, ll v) {
        access(u); T[u].self = v; pull(u);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, p, q; cin >> n >> m >> p >> q;
    using a3 = array<int, 3>;
    vector<a3> edges(n-1 + m);
    LinkCut lct(n);
    vector<vii> init_adj(n);
    rep(i, 0, n-1) {
        rep(j, 0, 3) cin >> edges[i][j];
        lct.Link(edges[i][0], edges[i][1]);
        edges[i][0]--, edges[i][1]--;
        init_adj[edges[i][0]].emplace_back(edges[i][1], edges[i][2]);
        init_adj[edges[i][1]].emplace_back(edges[i][0], edges[i][2]);
    }
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        for(auto [v, w] : init_adj[u]) if(v != p) {
            lct.Update(v+1, w);
            dfs(v, u, dfs);
        }
    };
    lct.reroot(1);
    dfs(0, -1, dfs);
    // vi par(n, -1), pedge(n);

    vi rem(m);
    vvi subsets(m);
    rep(i, 0, m) {
        int i1 = i + n-1;
        cin >> rem[i] >> edges[i1][0] >> edges[i1][1] >> edges[i1][2];
        rem[i]--;
        edges[i1][0]--, edges[i1][1]--;
    }

    vii tourists(p);
    rep(i, 0, p) {
        cin >> tourists[i].first >> tourists[i].second;
        tourists[i].first--, tourists[i].second--;
        subsets[tourists[i].first].push_back(tourists[i].second);
    }
    vii queries(q);
    rep(i, 0, q) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--, queries[i].second--;
        subsets[queries[i].first].push_back(queries[i].second);
    }
    rep(d, 0, m) {
        {
            auto [u, v, w] = edges[rem[d]];
            // lct.reroot(1);
            // if(lct.LCA(u+1, v+1) == v+1) swap(u, v);
            // lct.Update()
            lct.Cut(u+1, v+1);
        }
        {
            auto [u, v, w] = edges[n-1+d];
            lct.reroot(1);
            if(lct.LCA(1, v+1) != 0) swap(u, v);
            lct.Link(u+1, v+1);
            lct.Update(v+1, w);
        }

        sort(all(subsets[d]));
        subsets[d].erase(unique(all(subsets[d])), end(subsets[d]));
        // sort???????

        rep(i, 1, sz(subsets[d])) {
            int u = subsets[d][i-1], v = subsets[d][i];

        }
    }

    return 0;
}
