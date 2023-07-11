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
using a3 = array<ll, 3>;
using a2 = array<ll, 2>;

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

const ll inf = 1e12;
struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    // freopen("slingshot.in", "r", stdin);
    // freopen("slingshot.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vector<a3>> slingsa(2);
    vector<vector<a3>> qs(2);
    rep(i, 0, n){
        a3 p;
        rep(j, 0, 3){
            cin >> p[j];
        }
        slingsa[p[0] <= p[1]].pb(p);
    }
    vl ans(m, LLONG_MAX);
    rep(i, 0, m){
        a3 p;
        rep(j, 0, 2) cin >> p[j];
        p[2] = i;
        ans[i] = abs(p[0] - p[1]);
        qs[p[0] <= p[1]].pb(p);
    }
    for(auto &p : slingsa[1]){
        swap(p[0], p[1]);
    }
    for(auto &p : qs[1]) swap(p[0], p[1]);
    rep(direction, 0, 2){
        vector<a3> &slings = slingsa[direction];
        vector<a3> &queries = qs[direction];
        int n = sz(slings), m = sz(queries);
        map<ll, vpl> mm;
        sort(all(queries));
        for(auto &p : slings){
            mm[p[0]].pb({p[1], p[2]});
        }
        vector<vpl> ordered;
        vl okey;
        for(auto &p : mm){
            ordered.pb(p.s);
            okey.pb(p.f);
        }
        int pnter = 0;
        ll LIM = 1e9 + 1e7;
        // a x0 x b
        Node *case1 = new Node(0, LIM), *case2 = new Node(0, LIM);
        for(auto [x0, x, i] : queries){
            while(pnter < sz(okey) && okey[pnter] <= x0){
                ll a = okey[pnter];
                for(auto [b, t] : ordered[pnter]){
                    case1->set(b, b + 1, max(a - b - t, case1->query(b, b + 1)));
                    case2->set(b, b + 1, max(b + a - t, case2->query(b, b + 1)));
                }
                pnter++;
            }
            ans[i] = min(ans[i], x - x0 - (case1->query(x, LIM) + 2 * (x - x0)));
            ans[i] = min(ans[i], x - x0 - (case2->query(0, x + 1) - 2 * x0));
        }
        pnter = 0;
        reverse(all(okey));
        reverse(all(ordered));
        reverse(all(queries));
        Node *case3 = new Node(0, LIM), *case4 = new Node(0, LIM);
        for(auto [x0, x, i] : queries){
            while(pnter < sz(okey) && okey[pnter] >= x0){
                ll a = okey[pnter];
                for(auto [b, t] : ordered[pnter]){
                    case3->set(b, b + 1, max(-a - b - t, case3->query(b, b + 1)));
                    case4->set(b, b + 1, max(b - a - t, case4->query(b, b + 1)));
                }
                pnter++;
            }
            ans[i] = min(ans[i], x - x0 - (case3->query(x, LIM) + 2 * x));
            ans[i] = min(ans[i], x - x0 - (case4->query(0, x + 1)));
        }
        // rep(i, 0, sz(ordered))}{
        //     ll x0 = okey[i];
        //     vpl &qus = ordered[i];
            

        // }
    }
    for(ll a : ans){
        cout << a << "\n";
    }

    // add stuff for reordering answers at end
    return 0;
}