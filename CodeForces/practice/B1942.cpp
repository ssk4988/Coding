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

ll nc2(ll n){
    return n * (n+1) / 2;
}

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll mult = 0, lzmult = 0;
    ll sum = 0, basesum = 0, lzright = inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			sum = l->sum + r->sum;
		}
	}
    void build() {
        sum = basesum * mult;
    }
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return l->query(L, R) + r->query(L, R);
	}
    void setright(int L, int R, int idx) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            lzright = idx;
            basesum = nc2(idx - lo) - nc2(idx - hi);
            build();
        }
		else {
			push(), l->setright(L, R, idx), r->setright(L, R, idx);
			sum = l->sum + r->sum;
		}
	}
	void setmult(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            lzmult = x;
            mult = x;
            build();
        }
		else {
			push(), l->setmult(L, R, x), r->setmult(L, R, x);
			sum = l->sum + r->sum;
		}
	}
	void push() {
        if(lzmult){
            l->setmult(lo, hi, lzmult), r->setmult(lo, hi, lzmult), lzmult = 0;
        }
        if(lzright != inf){
            l->setright(lo, hi, lzright), r->setright(lo, hi, lzright), lzright = inf;
        }
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    vpl a(m);
    rep(i, 0, m) {cin >> a[i].f; a[i].f--; }
    rep(i, 0, m) cin >> a[i].s;
    sort(all(a));
    Node tree(0, n);
    set<int> loc;
    rep(i, 0, m){
        auto [x, v] = a[i];
        loc.insert(x);
        tree.setmult(x, x+1, 0);
        tree.setright(x, x+1, x);
        if(i > 0){
            auto [prevx, prevv] = a[i-1];
            tree.setright(prevx+1, x, x);
        }
        if(i+1 < m){
            auto [nextx, nextv] = a[i+1];
            tree.setmult(x+1, nextx, v);
        }
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int x, v; cin >> x >> v;
            x--;
            int prevx = *prev(loc.upper_bound(x)), nextx = *loc.upper_bound(x);
            tree.setright(prevx+1, x, x);
            tree.setmult(x+1, nextx, v);
            loc.insert(x);
            tree.setmult(x, x+1, 0);
            tree.setright(x, x+1, x);
        }
        else{
            int l, r; cin >> l >> r; l--;
            cout << tree.query(l, r) << "\n";
        }
    }

    
    return 0;
}