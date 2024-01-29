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
 * Author: Simon Lindholm
 * Date: 2016-07-25
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/DataStructure/LinkCut.h
 * Description: Represents a forest of unrooted trees. You can add and remove
 * edges (as long as the result is still a forest), and check whether
 * two nodes are in the same tree.
 * Time: All operations take amortized O(\log N).
 * Status: Stress-tested a bit for N <= 20
 */

struct Node { // Splay tree. Root's pp contains tree's parent.
	Node *p = 0, *pp = 0, *c[2];
	bool flip = 0;
	Node() { c[0] = c[1] = 0; fix(); }
	void fix() {
		if (c[0]) c[0]->p = this;
		if (c[1]) c[1]->p = this;
		// (+ update sum of subtree elements etc. if wanted)
	}
	void pushFlip() {
		if (!flip) return;
		flip = 0; swap(c[0], c[1]);
		if (c[0]) c[0]->flip ^= 1;
		if (c[1]) c[1]->flip ^= 1;
	}
	int up() { return p ? p->c[1] == this : -1; }
	void rot(int i, int b) {
		int h = i ^ b;
		Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
		if ((y->p = p)) p->c[up()] = y;
		c[i] = z->c[i ^ 1];
		if (b < 2) {
			x->c[h] = y->c[h ^ 1];
			y->c[h ^ 1] = x;
		}
		z->c[i ^ 1] = this;
		fix(); x->fix(); y->fix();
		if (p) p->fix();
		swap(pp, y->pp);
	}
	void splay() { /// Splay this up to the root. Always finishes without flip set.
		for (pushFlip(); p; ) {
			if (p->p) p->p->pushFlip();
			p->pushFlip(); pushFlip();
			int c1 = up(), c2 = p->up();
			if (c2 == -1) p->rot(c1, 2);
			else p->p->rot(c2, c1 != c2);
		}
	}
	Node* first() { /// Return the min element of the subtree rooted at this, splayed to the top.
		pushFlip();
		return c[0] ? c[0]->first() : (splay(), this);
	}
};

struct LinkCut {
	vector<Node> node;
	map<Node*, int> id;
	LinkCut(int N) : node(N) {
		rep(i, 0, N){
			id[&node[i]] = i;
		}
	}

	void link(int u, int v) { // add an edge (u, v)
		assert(!connected(u, v));
		makeRoot(&node[u]);
		node[u].pp = &node[v];
	}
	void cut(int u, int v) { // remove an edge (u, v)
		Node *x = &node[u], *top = &node[v];
		access(x); x->splay();
		Node *root = x->first();
		makeRoot(top); x->splay();
		assert(top == (x->pp ?: x->c[0]));
		if (x->pp) x->pp = 0;
		else {
			x->c[0] = top->p = 0;
			x->fix();
		}
		makeRoot(root);	
	}
	bool connected(int u, int v) { // are u, v in the same tree?
		Node* nu = access(&node[u])->first();
		return nu == access(&node[v])->first();
	}
	int lca(int u, int v) {
		Node *x = &node[u], *y = &node[v];
		accesslast(x);
		Node *lc = accesslast(y);
		return id[lc];
	}
	void makeRoot(Node* u) { /// Move u to root of represented tree.
		access(u);
		u->splay();
		if(u->c[0]) {
			u->c[0]->p = 0;
			u->c[0]->flip ^= 1;
			u->c[0]->pp = u;
			u->c[0] = 0;
			u->fix();
		}
	}
	Node* access(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
		u->splay();
		while (Node* pp = u->pp) {
			pp->splay(); u->pp = 0;
			if (pp->c[1]) {
				pp->c[1]->p = 0; pp->c[1]->pp = pp; }
			pp->c[1] = u; pp->fix(); u = pp;
		}
		return u;
	}
	Node* accesslast(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
		u->splay();
		if(u->c[1]){
			u->c[1]->p = 0; u->c[1]->pp = u;
		}
		u->c[1] = 0;
		u->fix();
		Node *last = u;
		while (Node *pp = u->pp) {
			last = pp;
			pp->splay(); u->pp = 0;
			if (pp->c[1]) {
				pp->c[1]->p = 0; pp->c[1]->pp = pp; }
			pp->c[1] = u; pp->fix(); u = pp;
		}
		return last;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    LinkCut lc(n);
	vi par(n);
	iota(all(par), 0);
    rep(i, 0, q){
        string t; cin >> t;
        if(t == "lca"){
			int a, b; cin >> a >> b; a--, b--;
            cout << (lc.lca(a, b) + 1) << "\n"; 
        }
        else if(t == "link"){
			int a, b; cin >> a >> b; a--, b--;
            lc.link(a, b);
			par[a] = b;
        }
        else{
			int a; cin >> a; a--;
            lc.cut(a, par[a]);
			par[a] = a;
		}
    }
    
    return 0;
}
