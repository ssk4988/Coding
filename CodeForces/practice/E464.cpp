#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vl pw;
const int N = 1e5 + 100;

struct S {
	int ones = 0;
	ll hash = 0;
};

S merge(S a, S b) {
	return {a.ones + b.ones, a.hash ^ b.hash};
}

struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
	S val;
	ll val = 0, lzadd = 0;
	PST(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(lo, mid); r = new PST(mid, hi);
			val = merge(l->val, r->val);
		}
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0; // idempotent
		if (L <= lo && hi <= R) return val;
		push();
		return merge(l->query(L, R), r->query(L, R));
	}
	PST* add(int v) {
		PST *n = new PST(*this);
		if(lo + 1 == hi) {
			return this;
		}
		int mid = lo + 
		if (L <= lo && hi <= R) {
			n->val += v;
			n->lzadd += v;
		} else {
			n->push();
			n->l = n->l->add(L, R, v);
			n->r = n->r->add(L, R, v);
			n->val = n->l->val + n->r->val;
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
    mt19937 rng(time(NULL));
	rep(i, 0, N) {
		pw.push_back(rng());
	}
    
    return 0;
}
