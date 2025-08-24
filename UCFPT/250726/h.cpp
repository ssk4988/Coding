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

struct WaveletTree {
    int n; vvi bv;
    WaveletTree(vl a, ll max_val) :
    n(sz(a)), bv(1+__lg(max_val), {{}}) {
        vl nxt(n);
        for(int h = sz(bv); h--; ) {
            vector<bool> b(n);
            rep(i, 0, n) b[i] = ((a[i] >> h)&1);
            bv[h] = vi(n+1);
            rep(i, 0, n) bv[h][i+1] = bv[h][i] + !b[i];
            array it{begin(nxt), begin(nxt) + bv[h][n]};
            rep(i, 0, n) *it[b[i]]++ = a[i];
            swap(a, nxt);
        }
    }
    ll kth(int l, int r, int k) {
        ll res = 0;
        for(int h = sz(bv); h--;) {
            int l0 = bv[h][l], r0 = bv[h][r];
            if(k < r0-l0) l = l0, r = r0;
            else k -= r0-l0, res |= 1ULL << h, l += bv[h][n] - l0, r += bv[h][n] - r0;
        }
        return res;
    }
    int count(int l, int r, ll ub) {
        int res = 0;
        for(int h = sz(bv); h--;) {
            int l0 = bv[h][l], r0 = bv[h][r];
            if((~ub >> h) & 1) l = l0, r = r0;
            else res += r0-l0, l += bv[h][n]-l0,
            r += bv[h][n] - r0;
        }
        return res;
    }
};

const ll mod = 998244353;

ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e > 0; e >>= 1, b = b*b % mod)
        if(e & 1) res = res * b % mod;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-2) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi pre(n, -1), post(n);
    int t = 0, split;
    vvi groups;
    function<void(int, int)> flatten = [&](int cur, int prv) -> void {
        groups.back().push_back(cur);
        pre[cur] = t++;
        for(int nxt: adj[cur]) if(nxt != prv)
            flatten(nxt, cur);
        post[cur] = t;
    };

    vi roots;
    rep(i, 0, n) if(pre[i] == -1) {
        groups.push_back(vi());
        flatten(i, -1);
        roots.push_back(i);
        split = t;
    }

    vl pre_inv(n);
    rep(i, 0, n)
        pre_inv[pre[i]] = n-i;

    WaveletTree tree(pre_inv, n);

    // count extra edges spanning tree containing node 0
    ll cnt = 0;
    for(int u: groups[0]) {
        cnt = (cnt + tree.count(pre[u], post[u], n-u));
        for(int v: adj[u])
            cnt -= v > u;
    }
    ll edges1 = modpow(2, cnt);

    // count extra edges spanning tree not containing node 0
    // (for all roots)

    ll init = 0;
    for(int u: groups[1]) {
        init = (init + tree.count(pre[u], post[u], n-u)) % mod;
        for(int v: adj[u])
            init -= v > u;
    }
    
    ll val = init, edges2 = 0;
    function<void(int, int)> reroot = [&](int cur, int prv) -> void {
        edges2 = (edges2 + modpow(2, val)) % mod;
        for(int nxt: adj[cur]) if(nxt != prv) {
            int L = pre[nxt], R = post[nxt];
            ll rem = tree.count(L, R, n-cur) - (nxt > cur); // good
            ll add = tree.count(0, n, n-nxt) - tree.count(L, R, n-nxt) - (cur > nxt); // good
            val += add - rem;
            reroot(nxt, cur);
            val -= add - rem;
        }
    };
    reroot(roots[1], -1);

    // count all extra edges spanning both subtrees
    ll edges3 = 0, sum = 0;
    function<void(int, int)> dfs = [&](int cur, int prv) -> void {
        edges3 = (edges3 + modpow(2, sum)) % mod;
        for(int nxt: adj[cur]) if(nxt != prv) {
            ll add = tree.count(split, n, n-nxt);
            sum += add;
            dfs(nxt, cur);
            sum -= add;
        }
    };
    dfs(0, -1);

    cerr << edges1 << " " << edges2 << " " << edges3 << endl;

    ll res = (edges1*edges2 % mod * edges3 % mod) % mod;
    cout << res << '\n';

    return 0;
}
