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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll madd = 0, val = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			comb();
		}
	}
    ll combine(int l, int r){
        return max(l, r);
    }
    void comb(){
        val = combine(l->val, r->val);
    }
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return combine(l->query(L, R), r->query(L, R));
	}
    ll pointquery(int idx){
        if(lo + 1 == hi) return val;
        int mid = lo + (hi - lo) / 2;
        push();
        if(mid <= idx) return r->pointquery(idx);
        else return l->pointquery(idx);
    }
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			comb();
		}
	}
	void push() {
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};
const bool DEBUG = false;
int main()
{
    if(!DEBUG){
        cin.tie(0)->sync_with_stdio(0);

    }
    cin.exceptions(cin.failbit);
    int n, k; ll a; cin >> n >> k >> a;
    vector<vpi> cx(k + 1), cy(k + 1);
    ll sumc = 0;
    rep(i, 0, n){
        int x, y, c; cin >> x >> y >> c;
        sumc += c;
        cx[x].pb({y, c});
        cy[y].pb({x, c});
    }
    Node tree(-1, k + 1);
    rep(i, 0, k + 1){
        for(auto [x, c] : cy[k - i]){
            tree.add(-1, x, c);
        }
        tree.add(-1, i - 1, -a);
        ll dp = tree.query(-1, i);
        if(DEBUG){
            rep(i, -1, k + 1){
                cout << "tree val at i=" << i << " is " << tree.pointquery(i) << nL;
            }
        }
        tree.add(i, i + 1, dp);
    }
    cout << (sumc - tree.query(-1, k + 1)) << nL;
    
    return 0;
}
