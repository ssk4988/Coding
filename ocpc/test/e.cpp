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

/*
add candidates to some global line container

for a path, the function is x * path length + path weight
centroid decomp
for a rooted tree, get all paths from root
can get best for each depth for each child subtree

line container representation:
list of y-intercepts (index is slope)
instead make it a list of slope,intercept pairs since some lines wont be on hull




how to make it a hull-
a,b in hull, add c
a.slope * x + a.y = b.slope * x + b.y
a.y - b.y = x * (b.slope - a.slope)
x = (a.y - b.y) / (b.slope - a.slope)

compare c.slope * (a.y - b.y) / (b.slope - a.slope) + c.y to a.slope * (a.y - b.y) / (b.slope - a.slope) + a.y

cross multiply to do - if c is higher, pop b


how to pair two line containers?
compare x-intersections with next line, cross multiply to compare


*/
using int128 = __int128_t;
using p11 = pair<int128, int128>;
vector<p11> tot;


void hullify(vector<p11> &source, vector<p11> &dest) {
    for(auto [cs, cy] : source) {
        while(sz(dest) >= 2) {
            auto [as, ay] = dest[sz(dest)-2];
            auto [bs, by] = dest[sz(dest)-1];
            bool rem = cs * (ay - by) + cy * (bs - as) >= as * (ay - by) + ay * (bs - as);
            if(rem) dest.pop_back();
            else break;
        }
        dest.push_back(p11{cs, cy});
    }
}
vector<p11> comb(vector<p11> &a, vector<p11> &b) {
    int l = 0, r = 0;
    while(l+1 < sz(a) || r+1 < sz(b)) {
        tot.push_back({a[l].f + b[r].f, a[l].s + b[r].s});
        bool doleft = false;
        if(r+1==sz(b)) {
            doleft = true;
        } else if(l+1 < sz(a)) {
            auto [a1s, a1y] = a[l];
            auto [a2s, a2y] = a[l+1];
            auto [b1s, b1y] = b[r];
            auto [b2s, b2y] = b[r+1];
            doleft = (a1y - a2y) * (b2s - b1s) <= (b1y - b2y) * (a2s - a1s);
        }
        if(doleft) l++;
        else r++;
    }
    if(sz(a) && sz(b)) {
        tot.push_back({a.back().f + b.back().f, a.back().s + b.back().s});
    }
    vector<p11> tmp, hull;
    l = 0, r = 0;
    while(l < sz(a) || r < sz(b)) {
        bool doleft = false;
        if(r == sz(b) || (l < sz(a) && a[l] < b[r])) {
            doleft = true;
        }
        p11 cur = doleft ? a[l] : b[r];
        if(sz(tmp) == 0 || cur.f != tmp.back().f) {
            tmp.push_back(cur);
        } else tmp.back().s = max(tmp.back().s, cur.s);
        if(doleft) l++;
        else r++;
    }
    hullify(tmp, hull);
    return hull;
}


template <class F, class G> struct centroid {
	G adj;
	F f;
	vi sub_sz, par;
	centroid(const G& adj, F f)
		: adj(adj), f(f), sub_sz(sz(adj), -1), par(sz(adj), -1) {
		rep(i, 0, sz(adj))
			if (sub_sz[i] == -1) dfs(i);
	}
	void calc_sz(int u, int p) {
		sub_sz[u] = 1;
		for (auto [v, _] : adj[u])
			if (v != p) calc_sz(v, u), sub_sz[u] += sub_sz[v];
	}
	int dfs(int u) {
		calc_sz(u, -1);
		for (int p = -1, sz_root = sub_sz[u];;) {
			auto big_ch = find_if(all(adj[u]), [&](pll x) {
                auto [v, _] = x;
				return v != p && 2 * sub_sz[v] > sz_root;
			});
			if (big_ch == end(adj[u])) break;
			p = u, u = big_ch->first;
		}
		f(adj, u);
		for (auto [v, _] : adj[u]) {
			iter_swap(find_if(all(adj[v]), [&](pll x) { return x.first == u; }), rbegin(adj[v]));
			adj[v].pop_back();
			par[dfs(v)] = u;
		}
		return u;
	}
};

ostream& operator<<(ostream &os, int128 v) {
    if(v == 0) return os << 0;
    vi digs;
    while(v) {
        digs.push_back(v % 10);
        v /= 10;
    }
    reverse(all(digs));
    for(auto x : digs) os << x;
    return os;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vll> g(n);
    rep(i, 0, n-1) {
        int u, v; ll w; cin >> u >> v >> w; u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    centroid(g, [&](vector<vll> &adj, int root) -> void {
        vector<vector<p11>> hulls;
        // cerr << "centroid " << root << endl;
        for(auto [c, iw] : adj[root]) {
            vector<p11> ds;
            ds.push_back(p11{0, 0});
            auto dfs = [&](int u, int p, int128 dw, int d, auto &&dfs) -> void {
                if(d >= sz(ds)) ds.push_back(p11{d, 0});
                ds[d].s = max(ds[d].s, dw);
                for(auto [v, w] : adj[u]) if(v != p) {
                    dfs(v, u, dw + w, d+1, dfs);
                }
            };
            dfs(c, root, iw, 1, dfs);
            // for(auto [s, y] : ds) {
            //     cerr << "centroid " << root << " child " << c << " l s=" << s << " y=" << y << endl;
            // }
            hulls.push_back({});
            hullify(ds, hulls.back());
            // for(auto [s, y] : hulls.back()) {
            //     cerr << "centroid " << root << " child " << c << " after hullify l s=" << s << " y=" << y << endl;
            // }
            for(auto [a, b] : hulls.back()) tot.push_back({a, b});
        }
        // cerr << "processed subtrees" << endl;
        for(int i = 0; i+1 < sz(hulls); i += 2) {
            hulls.push_back(comb(hulls[i], hulls[i+1]));
            // for(auto [s, y] : hulls.back()) {
            //     cerr << "centroid " << root << " new hullify step " << i << " s=" << s << " y=" << y << endl;
            // }
            hulls[i] = hulls[i+1] = vector<p11>();
        }
        // cerr << "done merging" << endl;
    });
    // cerr << "tot: " << endl;
    // for(auto [s, y] : tot) cerr << "line s=" << s << " y=" << y << endl;
    // cerr << "after hullify: " << endl;
    vector<p11> tmp(n+1);
    rep(i, 0, sz(tmp)) tmp[i].f = i, tmp[i].s = -1;
    for(auto [s, y] : tot) tmp[s].s = max(tmp[s].s, y);
    tmp[0].s = 0;
    // cerr << "tmp: " << endl;
    // for(auto [s, y] : tmp) cerr << "line s=" << s << " y=" << y << endl;
    while(tmp.back().s == -1) tmp.pop_back();
    // cerr << "tmp: " << endl;
    // for(auto [s, y] : tmp) cerr << "line s=" << s << " y=" << y << endl;
    // cerr << "after hullify: " << endl;
    tot.clear();
    hullify(tmp, tot);
    // for(auto [s, y] : tot) cerr << "line s=" << s << " y=" << y << endl;
    vector<int128> qs;
    qs.push_back(0);
    int p = 0;
    rep(qid, 0, m) {
        ll dc; cin >> dc;
        qs.push_back(qs.back() + dc);
    }
    for(auto cur : qs) {
        while(p+1 < sz(tot)) {
            auto [as, ay] = tot[p];
            auto [bs, by] = tot[p+1];
            if (cur * (bs - as) >= ay - by) p++;
            else break;
        }

        cout << ll(tot[p].f * cur + tot[p].s) << "\n";
    }


    return 0;
}
