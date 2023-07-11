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

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
    bool x = 0;
    pi suff = {1, 0}, pref = {1, 0}, best = {1, 0};
	Node(int val) : val(val), y(rand()) {
        suff.s = pref.s = best.s = val;
    }
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
pi bst(Node *n) { return n ? n->best : pi{0, 0}; }
pi prf(Node *n) { return n ? n->pref : pi{0, 0}; }
pi sff(Node *n) { return n ? n->suff : pi{0, 0}; }
void Node::recalc() { 
    c = cnt(l) + cnt(r) + 1;
    pref = prf(l);
    if(cnt(l) == pref.f && val == pref.s){
        pref.f += 1;
    }
    if(!l) pref = {1, val};
    if(cnt(l) + 1 == pref.f && prf(r).s == pref.s){
        pref.f += prf(r).f;
    }
    suff = sff(r);
    if(cnt(r) == suff.f && val == suff.s){
        suff.f += 1;
    }
    if(!r) suff = {1, val};
    if(cnt(r) + 1 == suff.f && sff(l).s == suff.s){
        suff.f += sff(l).f;
    }
    best = max(bst(l), bst(r));
    pi best1 = {1, val};
    if(sff(l).s == val) best1.f += sff(l).f;
    if(prf(r).s == val) best1.f += prf(r).f;
    best = max(best, best1);
    best = max(best, max(pref, suff));
}

void f(Node *t){
    if(t == NULL) return;
    t->x ^= 1;
    t->val ^= 1;
    t->best.s ^= 1;
    t->pref.s ^= 1;
    t->suff.s ^= 1;
}
void prop(Node *t){
    if(!t || !t->x) return;
    t->x = 0;
    f(t->l);
    f(t->r);
}
template<class F> void each(Node* n, F f) {
	if (n) { prop(n); each(n->l, f); f(n->val); each(n->r, f); }
}
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
    prop(n);
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
    prop(r);
    prop(l);
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

void flip(Node*& t, int l, int r) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	f(b);
    t = merge(a, merge(b, c));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    string str; cin >> str;
    Node *treap = NULL;
    rep(i, 0, n){
        treap = merge(treap, new Node(str[i] - '0'));
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int l, r; cin >> l >> r;
            l--,r--;
            flip(treap, l, r + 1);
            cout << treap->best.f << nL;
        }
        // each(treap, [](int val)->void{cout << val << " ";});
    }
    
    return 0;
}