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

typedef uint64_t ull;
static int C;

template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return pair{x, b} == pair{o.x, o.b}; }
	bool operator<(A o) const { return pair{x, b} < pair{o.x, o.b}; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

vector<H> pw;

struct S {
    int size=1, val=0;
	// h0 is the current guy
	H h0=0, h1=pw[0];
};

S merge(S a, S b) {
	return {a.size + b.size, a.val, a.h0 * pw[b.size] + b.h0, a.h1 * pw[b.size] + b.h1};
}

struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
	S val;
	bool sw = false;
	PST(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(lo, mid); r = new PST(mid, hi);
			val = merge(l->val, r->val);
		}
	}
	PST* inv(int L, int R) {
		if (R <= lo || hi <= L) return this;
		PST *n;
		if (L <= lo && hi <= R) {
			n = new PST(*this);
			n->sw = !n->sw;
			n->val.val = 1 - n->val.val;
			swap(n->val.h0, n->val.h1);
		} else {
			push();
			n = new PST(*this);
			n->l = l->inv(L, R);
			n->r = r->inv(L, R);
			n->val = merge(n->l->val, n->r->val);
		}
		return n;
	}
	void print() {
		if(l) push(), l->print(), r->print();
		else cout << val.val;
	}
	void push() {
		if(!sw) return;
		l = l->inv(lo, hi);
		r = r->inv(lo, hi);
		sw = false;
	}
};

int comp(PST *a, PST *b) {
	if(!(a->l)) {
		return a->val.val - b->val.val;
	}
	if(a->val.h0 == b->val.h0) return 0;
	a->push(), b->push();
	int l = comp(a->l, b->l);
	if(l != 0) return l;
	return comp(a->r, b->r);
}


#include <sys/time.h>
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
	
	pw.push_back(1);
	int n, q; cin >> n >> q;

	rep(i, 0, n+100){
		pw.push_back(pw.back() * C);
	}

	PST *cur = new PST(0, n);
	PST *best = cur;
	rep(i, 0, q) {
		int l, r; cin >> l >> r; l--;
		cur = cur->inv(l, r);
		int c = comp(cur, best);
		if(c > 0) best = cur;
		// cerr << "cur: ";
		// cur->print();
		// cerr << " best: ";
		// best->print();
		// cerr << endl;
	}
	best->print();
	cout << "\n";
	
    
    return 0;
}
