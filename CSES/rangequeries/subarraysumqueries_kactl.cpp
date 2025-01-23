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

struct subarray {
    ll sum = 0, pref=0, suff=0, ans=0;
    subarray(ll v=0) {
        // v = max(v, 0LL);
        sum = pref = suff = ans = v;
    }
};

subarray op(subarray l, subarray r) {
    subarray res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    subarray val;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = op(l->val, r->val);
		}
		
	}
	subarray query(int L, int R) {
		if (R <= lo || hi <= L) return subarray();
		if (L <= lo && hi <= R) return val;
		push();
		return op(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) val = x;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = op(l->val, r->val);
		}
	}
	
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    Node tree(0, n);
    rep(i, 0, n) tree.set(i,i+1, a[i]);

    rep(i, 0, m){
        int k, x; cin >> k >> x; k--;
        tree.set(k, k+1, x);
        cout << max(0LL, tree.query(0, n).ans) << nL;
    }



    
    return 0;
}
