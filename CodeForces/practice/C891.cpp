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

struct RollbackUF {
	vi e; vector<pi> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct Edge{
    int id, a, b;
    ll w;
    int operator<(Edge &o){
        return w < o.w;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<Edge> edges(m), se;
    rep(i, 0, m){
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
        edges[i].a--;edges[i].b--;
        edges[i].id = i;
        se.pb(edges[i]);
    }
    sort(all(se));
    int q; cin >> q;
    vi ans(q, 1);
    vector<pair<pi, vi>> order;
    rep(i, 0, q){
        int k; cin >> k;
        vi v(k);
        rep(j, 0, k){
            cin >> v[j];
            v[j]--;
        }
        sort(all(v), [&](int a, int b)->bool{return edges[a] < edges[b];});
        vi v1;
        rep(j, 0, k){
            if(j > 0 && edges[v[j]].w != edges[v[j - 1]].w){
                order.pb({{edges[v1.back()].w, i}, vi(v1)});
                v1.clear();
            }
            v1.pb(v[j]);
        }
        if(sz(v1)){
            order.pb({{edges[v1.back()].w, i}, vi(v1)});
        }
    }
    sort(all(order));
    int pnt = 0;
    RollbackUF uf(n);
    for(auto [p, v] : order){
        auto [w, idx] = p;
        while(pnt < m && se[pnt].w < w){
            uf.join(se[pnt].a, se[pnt].b);
            pnt++;
        }
        int t = uf.time();
        for(int eid : v){
            if(!uf.join(edges[eid].a, edges[eid].b)){
                ans[idx] = false;
            }
        }
        uf.rollback(t);
    }
    rep(i, 0, q){
        cout << (ans[i] ? "YES" :"NO") << nL;
    }

    
    return 0;
}
