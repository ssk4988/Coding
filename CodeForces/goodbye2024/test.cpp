#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
	ll val = 0, lzadd = 0;
	PST(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(v, lo, mid); r = new PST(v, mid, hi);
			val = l->val + r->val;
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0; // idempotent
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	PST* add(int L, int R, ll v) {
		if (R <= lo || hi <= L) return this;
		PST *n;
		if (L <= lo && hi <= R) {
			n = new PST(*this);
			n->val += v;
			n->lzadd += v;
		} else {
			push();
			n = new PST(*this);
			n->l = l->add(L, R, v);
			n->r = r->add(L, R, v);
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

mt19937 rng;
int main(){

	vector<ll> tmp(10);
	PST *pst = new PST(tmp,0,10);
	cout << pst->val << "a\n";
	cout << pst << "\n";
	pst = pst->add(4,5,123);
	cout << pst << "\n";
	cout << pst->val << "\n";
	cout << pst->query(0,10) << "b\n";
	return 0;
}