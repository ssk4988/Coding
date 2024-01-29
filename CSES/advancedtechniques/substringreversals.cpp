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

/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
    bool rev = false;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
	void push();
    void tag() {
        rev = !rev;
        swap(l, r);
    }
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }
void Node::push() {
    if(rev){
        rev = false;
        if(l) l->tag();
        if(r) r->tag();
    }
}

template<class F> void each(Node* n, F f) {
	if (n) { n->push(); each(n->l, f); f(n->val); each(n->r, f); }
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
    b->tag();
    t = merge(merge(a, b), c);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    Node *treap = NULL;
    string str; cin >> str;
    rep(i, 0, n){
        treap = merge(treap, new Node(str[i] - 'A'));
    }
    auto dfs = [&](Node *cur, auto &&dfs)->void{
        if(cur == NULL) return;
        cur->push();
        dfs(cur->l, dfs);
        cout << char(cur->val + 'A');
        dfs(cur->r, dfs);
    };
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--, b--;
        rev(treap, a, b + 1);

        // dfs(treap, dfs);
        // cout << nL;
    }
    dfs(treap, dfs);
    cout << nL;
    
    return 0;
}
