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

ll n, k;
vl a;

void *atree;

const ll inf = 1e9 + 10;
struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, mset = -inf, val = inf;
	Node(ll lo,ll hi):lo(lo),hi(hi){
        if(hi - lo >= n){
            val = ((Node*)atree)->query(0, n);
            return;
        }
        ll lv = lo % n, rv = hi % n;
        if(rv == 0) rv += n;
        if(lv < rv){
            val = ((Node*)atree)->query(lv, rv);
        }
        else{
            val = min(((Node*)atree)->query(lv, n), ((Node*)atree)->query(0, rv));
        }
        return;
    } // Large interval of inf
	Node(vl& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = min(l->val, r->val);
		}
		else val = v[lo];
	}
	ll query(ll L, ll R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != -inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = -inf;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    a.resize(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    atree = new Node(a, 0, n);
    Node *tree = new Node(0, n * k);
    int q; cin >> q;
    rep(i, 0, q){
        int t, l, r, x; cin >> t;
        cin >> l >> r;l--,r--;
        if(t == 1){
            cin >> x;
            tree->set(l, r + 1, x);
        }
        else{
            cout << tree->query(l, r + 1) << nL;
        }
    }

    
    return 0;
}