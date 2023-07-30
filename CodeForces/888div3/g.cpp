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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        UF uf(n);
        vvi adj(n);
        vi h(n);
        rep(i, 0, n) cin >> h[i];
        rep(i, 0, m){
            int a, b; cin >> a >> b;
            a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        int q; cin >> q;
        vi ans(q);
        // h[a] + e, i, a, b
        vector<array<int, 4>> qs;
        rep(i, 0, q){
            int a, b, e; cin >> a >> b >> e;
            a--,b--;
            int c = h[a] + e;
            qs.pb({c, i, a, b});
        }
        sort(all(qs));
        vi order;
        rep(i, 0, n){
            order.pb(i);
        }
        sort(all(order), [&](int a, int b)->bool{return h[a] < h[b];});
        int pnt = 0;
        rep(i, 0, q){
            auto [c, idx, a, b] = qs[i];
            while(pnt < n && h[order[pnt]] <= c){
                for(int nex : adj[order[pnt]]) if(h[nex] <= c) uf.join(nex, order[pnt]);
                pnt++;
            }
            ans[idx] = uf.sameSet(a, b);
        }
        rep(i, 0, q) cout << (ans[i] ? "YES" : "NO") << nL;
    }
    
    return 0;
}