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

using ap2 = array<pi, 2>;
const int inf = 1e9;
struct rect {
    ap2 maxx = {pi{INT_MIN, -1}, pi{INT_MIN, -1}}, maxy = {pi{INT_MIN, -1}, pi{INT_MIN, -1}}
    , minx = {pi{INT_MAX, -1}, pi{INT_MAX, -1}}, miny = {pi{INT_MAX, -1}, pi{INT_MAX, -1}};
    void addx(pi v){
        if(v.f == INT_MIN || v.f == INT_MAX) return;
        rep(i, 0, 2){
            if(v == maxx[i] || v == minx[i]) return;
        }
        if(v > maxx[0]){ swap(maxx[1], maxx[0]); maxx[0] = v;}
        else if(v > maxx[1]) maxx[1] = v;
        if(v < minx[0]){ swap(minx[1], minx[0]); minx[0] = v;}
        else if(v < minx[1]) minx[1] = v;
    }
    void addy(pi v){
        if(v.f == INT_MIN || v.f == INT_MAX) return;
        rep(i, 0, 2){
            if(v == maxy[i] || v == miny[i]) return;
        }
        if(v > maxy[0]){ swap(maxy[1], maxy[0]); maxy[0] = v;}
        else if(v > maxy[1]) maxy[1] = v;
        if(v < miny[0]){ swap(miny[1], miny[0]); miny[0] = v; }
        else if(v < miny[1]) miny[1] = v;
    }
};
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    rect val;
	Node(vpi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = comb(l->val, r->val);
		}
		else {
            // TODO
            val.addx({v[lo].f, lo});
            val.addy({v[lo].s, lo});
        }
	}
    rect comb(rect a, rect b){
        rect res;
        rep(i, 0, 2){
            res.addx(a.maxx[i]);
            res.addx(a.minx[i]);
            res.addx(b.maxx[i]);
            res.addx(b.minx[i]);
            res.addy(a.maxy[i]);
            res.addy(a.miny[i]);
            res.addy(b.maxy[i]);
            res.addy(b.miny[i]);
        }
        return res;
    }
	rect query(int L, int R) {
		if (R <= lo || hi <= L){
            rect v;
            return v;
        }
		if (L <= lo && hi <= R) return val;
		return comb(l->query(L, R), r->query(L, R));
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vpi v(n);
    rep(i, 0, n){
        cin >> v[i].f >> v[i].s;
    }
    Node tree(v, 0, n);
    // cout << "built tree" << nL;
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--, b--;
        rect res = tree.query(a, b + 1);
        // cout << "idxs: " << res.minx[0].s << " " << res.minx[1].s << " " << res.maxx[0].s << " " << res.maxx[1].s << " " << res.miny[0].s << " " << res.miny[1].s << " " << res.maxy[0].s << " " << res.maxy[1].s << nL;
        ll ans = LLONG_MAX;
        set<int> idx;
        idx.insert(res.maxx[0].s);
        idx.insert(res.minx[0].s);
        idx.insert(res.maxy[0].s);
        idx.insert(res.miny[0].s);
        for(int ix : idx){
            ll maxx = res.maxx[res.maxx[0].s == ix ? 1 : 0].f;
            ll minx = res.minx[res.minx[0].s == ix ? 1 : 0].f;
            ll maxy = res.maxy[res.maxy[0].s == ix ? 1 : 0].f;
            ll miny = res.miny[res.miny[0].s == ix ? 1 : 0].f;
            ll d = max(maxx - minx, maxy - miny);
            ans = min(ans, d);
        }
        cout << ans << nL;
    }
    
    return 0;
}
