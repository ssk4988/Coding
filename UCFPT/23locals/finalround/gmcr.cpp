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

const bool DEBUG = false;
const int N = 1e5 + 1;
struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
	ll val = 0, lzadd = 0, sum = 0;
	PST(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(lo, mid); r = new PST(mid, hi);
		}
	}
	ll query(int idx) {
        if(lo + 1 == hi) return sum;
        int mid = lo + (hi - lo) / 2;
		push();
        if(mid <= idx) return l->sum + r->query(idx);
        else return l->query(idx);
	}
	PST * add(int L, int R, ll v) {
		if (R <= lo || hi <= L) return this;
        if(DEBUG && lo == 0 && hi == N){
            cout << "calling " << v << " with L=" << L << " and R=" << R << nL;
        }
        PST *n;
		if (L <= lo && hi <= R) {
            if(DEBUG){
                cout << "adding " << v << " to [" << lo << ", " << hi << "]" << nL;
            }
            n = new PST(*this);
			n->val += v;
			n->lzadd += v;
            n->sum += (hi - lo) * v;

		} else {
            push();
            n = new PST(*this);
			n->l = l->add(L, R, v);
			n->r = r->add(L, R, v);
            n->sum = n->l->sum + n->r->sum;
		}
        if(DEBUG){
            // cout << "sum on [" << lo << "," << hi << "] is now " << n->sum << nL;
        }
		return n;
	}
	void push() {
		if(lzadd == 0) return;
		l = l->add(lo, hi, lzadd);
		r = r->add(lo, hi, lzadd);
		lzadd = 0;
	}
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    
    ll precut = 1e15;
    PST *tree = new PST(0, N);
    PST *lasttree = tree;
    rep(i, 0, q){
        char c; cin >> c;
        if(c == 'A'){
            int l, k; cin >> l >> k; l--;
            int start = l - k + 1;
            if(start < 0){
                // first needs to have different value
                tree = tree->add(0, 1, k - l);
                if(l > 0) tree = tree->add(1, l + 1, 1);
            }
            else tree = tree->add(start, l + 1, 1);
            int left = l + 1, right = min(N, l + 1 + k - 1 + 1);
            if(left < right) tree = tree->add(left, right, -1);
        }
        else if(c == 'B'){
            int idx; cin >> idx; idx--;
            ll preval = lasttree->query(idx);
            if(DEBUG) cout << "preval is " << preval << nL;
            ll ans = tree->query(idx) - preval + min(preval, precut);
            cout << ans << nL;
        }
        else{
            ll h; cin >> h;
            lasttree = tree;
            precut = h;
        }
    }
    
    return 0;
}
