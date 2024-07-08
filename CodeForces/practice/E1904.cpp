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

struct Node {
    int lo, hi;
    int active=1;
    int val = 0, useval = 0;
    int lzadd = 0, lzactive = 0;
    Node *l = 0, *r = 0;
    Node(vi &v, int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid), r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        } else val = v[lo];
        useval = val;
    }
    void add(int L, int R, int v) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            lzadd += v;
            val += v;
            useval = active ? val : 0;
            return;
        }
        push();
        l->add(L, R, v), r->add(L, R, v);
        val = max(l->val, r->val);
        useval = max(l->active ? l->useval : 0, r->active ? r->useval : 0);
        active = l->active || r->active;
    }
    void activate(int L, int R, int v) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            active = v;
            lzactive = 1;
            useval = active ? val : 0;
            return;
        }
        push();
        l->activate(L, R, v), r->activate(L, R, v);
        val = max(l->val, r->val);
        useval = max(l->active ? l->useval : 0, r->active ? r->useval : 0);
        active = l->active || r->active;
    }
    void push() {
        if(lzadd) {
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd), lzadd = 0;
        }
        if(lzactive) {
            l->activate(lo, hi, active), r->activate(lo, hi, active), lzactive = 0;
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi depth(n), tin(n), subsz(n, 1), par(n, -1);
    int T = 0;
    auto dfs = [&](int u, int p, auto &&dfs) ->void {
        tin[u] = T++;
        par[u] = p;
        if(p != -1) {
            adj[u].erase(find(all(adj[u]), p));
        }
        for(int v : adj[u]){
            // if(v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, dfs);
            subsz[u] += subsz[v];
        }
    };
    dfs(0, -1, dfs);
    vi segarr(n);
    rep(i, 0, n){
        segarr[tin[i]] = depth[i];
    }
    Node tree(segarr, 0, n);
    vector<vvi> queries(n);
    vvi qidx(n);
    rep(i, 0, q){
        int x, c; cin >> x >> c; x--;
        qidx[x].pb(i);
        vi v(c);
        rep(j, 0, c){
            cin >> v[j]; v[j]--;
        }
        queries[x].pb(v);
    }
    vi path;
    vi ans(q);
    auto calc = [&](int u, auto &&calc) -> void {
        path.pb(u);
        rep(t, 0, sz(qidx[u])){
            int qid = qidx[u][t];
            auto &ps = queries[u][t];
            sort(all(ps), [&](int a, int b) -> bool { return tin[a] < tin[b]; });
            tree.activate(0, n, 1);
            for(int v : ps){
                if(depth[v] < sz(path) && path[depth[v]] == v){
                    tree.activate(0, n, 0);
                    int under = path[depth[v]+1];
                    tree.activate(tin[under], tin[under] + subsz[under], 1);
                }
                else tree.activate(tin[v], tin[v] + subsz[v], 0);
            }
            ans[qid] = tree.useval;
        }
        for(int v : adj[u]){
            tree.add(0, n, 1);
            tree.add(tin[v], tin[v] + subsz[v], -2);
            calc(v, calc);
            tree.add(0, n, -1);
            tree.add(tin[v], tin[v] + subsz[v], 2);
        }
        path.pop_back();
    };
    calc(0, calc);
    rep(i, 0, q){
        cout << ans[i] << "\n";
    }

    return 0;
}
