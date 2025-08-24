#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
const int inf = 1e9 + 10;

struct FT{
    vector<ll> s;
    FT(int n): s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;

    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if(sum <= 0) return -1;
        int pos = 0;
        for(int pw = 1 << 25; pw; pw >>= 1) {
            if(pos + pw <= sz(s)&& s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};
struct Node {
    int lo, hi;
    pii val{inf, -1};
    int lz = 0;
    Node *l=0, *r=0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    pii query(int L, int R) {
        if(R <= lo || hi <= L) return pii{inf, -1};
        if(L <= lo && hi <= R) return val;
        push();
        return min(l->query(L, R), r->query(L, R));
    }
    void set(int idx, pii v) {
        if(lo + 1 == hi) {
            val = v;
            return;
        }
        push();
        int mid = lo + (hi - lo) / 2;
        if(mid <= idx) r->set(idx, v);
        else l->set(idx, v);
        val = min(l->val, r->val);
    }
    void add(int L, int R, int v) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R){
            if(val.first == inf) return;
            val.first += v;
            lz += v;
            return;
        }
        push();
        l->add(L, R, v), r->add(L, R, v);
        val = min(l->val, r->val);
    }
    void push() {
        if(lz == 0) return;
        l->add(lo, hi, lz), r->add(lo, hi, lz);
        lz = 0;
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret, depth;
    Node *tree;

    LCA(vector<vi>& C) : time(sz(C), -1) {
        depth = vi(sz(C));
        dfs(C, 0, -1);
        tree = new Node(0, sz(ret));
        rep(i, 0, sz(ret)) {
            tree->set(i, pii{ret[i], i});
        }
    }
    void dfs(vector<vi>& C, int cur, int par) {
        time[cur] = T++;
        for(int nxt : C[cur]) if(nxt != par) {
            depth[nxt] = depth[cur] + 1;
            path.push_back(cur), ret.push_back(time[cur]);
            dfs(C, nxt, cur);
        }
    }
    int lca(int a, int b) {
        if(a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        // auto [c, d] = tree->query(a, b);
        // cerr << "c=" << c << " d=" << d << endl;
        return path[(tree->query(a, b)).second];
    }
    int dist(int a, int b) {
        if(a == b) return 0;
        // cerr << "lca is " << lca(a, b) << endl;
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    n++;
    vi par(n, -1);
    vi w(n), s(n);
    priority_queue<pii, vii, greater<>> wpq, spq;
    int have = 1;
    vvi child(n);
    FT ft(n);
    int cent = 0;
    rep(i, 1, n) {
        cin >> par[i] >> w[i] >> s[i];
        child[par[i]].push_back(i);
        wpq.push({w[i], i});
    }
    int T = 0;
    vi tin(n), subsz(n, 1), tout(n);
    auto dfs = [&](int u, auto &&dfs) -> void {
        tin[u] = T++;
        for(int v : child[u]) {
            dfs(v, dfs);
            subsz[u] += subsz[v];
        }
        tout[u] = T;
        sort(all(child[u]), [&](int a, int b) { return tin[a] < tin[b]; });
    };
    dfs(0, dfs);
    ft.update(tin[0], 1);
    Node tree(0, n);
    int curt = 0;
    vi tactive(n, -1), tcollect(n, -1);
    LCA lca(child);
    rep(i, 0, n) assert(lca.time[i] != -1);
    while(true) {
        int t = inf;
        if(sz(wpq)) {
            t = min(t, wpq.top().first);
        }
        {
            auto [d, _] = tree.query(0, n);
            if(d != inf) t = min(t, curt + d);
        }
        if(sz(spq) && spq.top().first <= have-1) t = curt;
        // cerr << "next_t = " << t << " cur t = " << t << " have " << have << " cent " << cent << endl;
        if(t == inf) break;
        int dt = t - curt;
        curt = t;
        tree.add(0, n, -dt);
        assert(curt == 0 || dt > 0);
        while(sz(wpq) && wpq.top().first == curt) {
            auto [_, u] = wpq.top(); wpq.pop();
            // cerr << "wpopped " << _ << " " << u << endl;
            spq.push({s[u], u});
        }
        auto spop = [&]() -> bool {
            bool did = false;
            while(sz(spq) && spq.top().first <= have-1){
                auto [_, u] = spq.top(); spq.pop();
                // cerr << "spopped " << _ << " " << u << endl;
                tree.set(tin[u], pii{lca.dist(u, cent), u});
                tactive[u] = curt;
                did = true;
            }
            return did;
        };
        queue<int> qactive;
        int curhave = have;
        int new_cent = cent;
        bool did = true;
        while(did) {
            did = false;
            // remove guys and move new centroid
            while(true) {
                if(spop()) did = true;
                auto [d_u, u] = tree.query(0, n);
                if(d_u > 0) break;
                did = true;
                // cerr << "activating " << u << endl;
                tcollect[u] = curt;
                have++;
                qactive.push(u);
                tree.set(tin[u], pii{inf, -1});
                ft.update(tin[u], 1);
                if(tout[u] <= tin[new_cent] || tout[new_cent] <= tin[u]) {
                    // check parent
                    assert(par[new_cent] != -1);
                    int sub = ft.query(tin[new_cent]) + ft.query(n) - ft.query(tout[new_cent]);
                    if(sub * 2 > have || (sub * 2 >= have && par[new_cent] > new_cent)) {
                        new_cent = par[new_cent];
                    }
                } else {
                    auto it = lower_bound(all(child[new_cent]), u, [&](int a, int b) { return tout[a] < tout[b]; });
                    assert(it != end(child[new_cent]));
                    int v = *it;
                    int sub = ft.query(tout[v]) - ft.query(tin[v]);
                    if(sub * 2 > have || (sub * 2 >= have && v > new_cent)) new_cent = v;
                }
            }
            if(did) continue;
            // move towards centroid
            if(cent != new_cent) {
                if(tin[new_cent] <= tin[cent] && tout[cent] <= tout[new_cent]) {
                    // parent
                    tree.add(tin[cent], tout[cent], 1);
                    tree.add(0, tin[cent], -1);
                    tree.add(tout[cent], n, -1);
                    cent = par[cent];
                } else {
                    auto it = lower_bound(all(child[cent]), new_cent, [&](int a, int b) { return tout[a] < tout[b]; });
                    assert(it != end(child[cent]));
                    int v = *it;
                    cent = v;
                    tree.add(tin[cent], tout[cent], -1);
                    tree.add(0, tin[cent], 1);
                    tree.add(tout[cent], n, 1);
                }
                did = true;
            }
        }
    }
    rep(i, 1, n) {
        cout << tactive[i] << " " << tcollect[i] << "\n";
    }

    return 0;
}
