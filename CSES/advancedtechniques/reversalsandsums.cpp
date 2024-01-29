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
    ll sum;
    bool rev = false;
	Node(int val) : val(val), y(rand()), sum(val) {}
	void recalc();
    void push(){
        if(rev == 0) return;
        // swap(l, r);
        if(l){
            l->rev ^= 1;
            swap(l->l, l->r);
        }
        if(r){
            r->rev ^= 1;
            swap(r->l, r->r);
        }
        rev = 0;
    }
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sumf(Node* n) { return n ? n->sum : 0; }
void Node::recalc() { 
    c = cnt(l) + cnt(r) + 1; 
    sum = sumf(l) + sumf(r) + val;
}

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
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
    l->push();
    r->push();
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
void rev(Node*& t, int l, int r) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
    b->rev ^= 1;
    swap(b->l, b->r);
    t = merge(merge(a, b), c);
}
ll getsum(Node*& t, int l, int r) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
    ll v = b->sum;
    t = merge(merge(a, b), c);
    return v;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    Node *treap = NULL;
    rep(i, 0, n){
        int k; cin >> k;
        treap = merge(treap, new Node(k));
    }
    auto dfs = [&](Node *cur, auto &&dfs)->void{
        if(cur == NULL) return;
        cur->push();
        dfs(cur->l, dfs);
        cout << cur->val << nL;
        dfs(cur->r, dfs);
    };
    rep(i, 0, m){
        int t; cin >> t;
        int a, b; cin >> a >> b;
        a--, b--;
        if(t == 1)rev(treap, a, b + 1);
        else cout << getsum(treap, a, b + 1) << nL;
        // dfs(treap, dfs);
        // cout << nL;
    }
    // dfs(treap, dfs);
    // cout << nL;
    
    return 0;
}
