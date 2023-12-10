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
    pi mn;
	Node(int val) : val(val), y(rand()), mn(val, 0) {}
	void recalc();
    void push();
    void tag();
    bool sw = false;
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { 
    c = cnt(l) + cnt(r) + 1; 
    mn = make_pair(val, cnt(l));
    if(l) mn = min(mn, l->mn);
    if(r) mn = min(mn, make_pair(r->mn.f, r->mn.s + 1 + cnt(l)));
}
void Node::tag(){
    sw = !sw;
    mn.s = cnt(this) - 1 - mn.s;
    swap(l, r);
}
void Node::push() {
    if(sw){
        sw = false;
        if(l) l->tag();
        if(r) r->tag();
    }
}

template<class F> void each(Node* n, F f) {
	if (n) { n->push(); each(n->l, f); f(n); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
    n->push();
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
    l->push(), r->push();
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

// reverse the range [l, r)
void rev(Node*& t, int l, int r) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
    b->tag();
    t = merge(a, merge(b, c));
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    Node *root = NULL, *p;
    rep(i, 0, n){
        int v; cin >> v;
        root = ins(root, new Node(v), i);
    }
    vpi ans;
    rep(i, 0, n){
        int mindex = root->mn.s;
        ans.push_back({i + 1, i + 1 + mindex});
        rev(root, 0, mindex + 1);
        tie(p, root) = split(root, 1);
        // each(root, [](Node *v) -> void {cout << v->val << " " << v->mn.f << " " << v->mn.s << "\n"; });
        // cout << "\n";
    }
    cout << sz(ans) << "\n";
    for(auto [a, b] : ans){
        cout << a << " " << b << "\n";
    }

    
    return 0;
}
