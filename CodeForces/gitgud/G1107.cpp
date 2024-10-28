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
    ll mset = inf, madd = 0, val = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = max(l->val, r->val);
		}
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

// f(r-l) = (r-l) * a - (pref(r)-pref(l)) - gap(l,r)^2
// get difference array on d -> v
// = ar - al - pref(r) + pref(l) - maxv(l, r)^2
// sweep on r
// ar - pref(r) +              [pref(l) - al - max^2]
// monotonic stack -> decreasing, know when certain ranges are

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; ll a; cin >> n >> a;
    Node tree(0, n);
    vl d(n), c(n);
    rep(i, 0, n){
        cin >> d[i] >> c[i];
    }
    for(int i = n-1; i > 0; i--) d[i] -= d[i-1];
    d.erase(begin(d));
    partial_sum(all(c), begin(c));
    c.insert(begin(c), 0);
    ll ans = 0;
    vpl st;
    st.pb({inf, -1});
    rep(r, 1, n+1){
        ll base = a * r - c[r];
        tree.add(r-1, r, c[r-1] - a * (r-1));
        if(r >= 2) {
            pl nxt = {d[r-2], r-2};
            int prv = r-2;
            while(sz(st) && st.back() < nxt) {
                auto [v, idx] = st.back();
                tree.add(idx, prv, (v*v));
                prv = idx;
                st.pop_back();
            }
            tree.add(prv, nxt.s+1, -d[r-2]*d[r-2]);
            nxt.s = prv;
            st.push_back(nxt);
        }
        ll best = tree.query(0, r);
        ans = max(ans, base + best);
    }
    cout << ans << "\n";

    
    
    return 0;
}
