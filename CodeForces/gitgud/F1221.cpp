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

const ll inf = 1e18;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll madd = 0;
    pl val = {0, 0};
	Node(vi &v, int lo,int hi):lo(lo),hi(hi){
        if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            val = comb(l->val, r->val);
		}
        else{
            val = {v[lo], v[lo]};
        }
    } // Large interval of -inf
    pl comb(pl a, pl b){
        return max(a, b);
    }
	pl query(int L, int R) {
		if (R <= lo || hi <= L) return {-inf, lo};
		if (L <= lo && hi <= R) return val;
		push();
		return comb(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val.f += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = comb(l->val, r->val);
		}
	}
	void push() {
		// if (!l) {
		// 	int mid = lo + (hi - lo)/2;
		// 	l = new Node(lo, mid); r = new Node(mid, hi);
		// }
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int LIM = 1e9 + 10;
    vector<array<int, 4>> events; // r, l, original r, c
    vi xs;
    rep(i, 0, n){
        int x, y, c; cin >> x >> y >> c;
        if(x > y) swap(x, y);
        events.pb({y, x, y, c});
        xs.pb(y);
        xs.pb(x);
    }
    sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());
    for(auto &[r, l, x, c] : events){
        r = lower_bound(all(xs), r) - xs.begin();
        l = lower_bound(all(xs), l) - xs.begin();
    }
    sort(all(events));
    Node tree(xs, 0, sz(xs));
    pair<ll, pl> best = {0, {2e9, 2e9}};
    rep(i, 0, sz(events)){
        auto [r, l, x, c] = events[i];
        tree.add(0, l+1, c);
        if(i + 1 >= sz(events) || events[i][0] < events[i+1][0]){
            pl cur = tree.query(0, r+1);
            cur.f -= x;
            best = max(best, {cur.f, {cur.s, x}});
        }
    }
    cout << best.f << "\n" << best.s.f << " " << best.s.f << " " << best.s.s << " " << best.s.s << "\n";
    
    return 0;
}
