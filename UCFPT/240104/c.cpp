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

struct Node { // Splay tree. Root's pp contains tree's parent.
	Node *p = 0, *pp = 0, *c[2];
	bool flip = 0;
    int sum = 1, w = 0;
	Node() { c[0] = c[1] = 0; fix(); }
	void fix() {
		if (c[0]) c[0]->p = this;
		if (c[1]) c[1]->p = this;
        sum = w;
        if(c[0]) sum += c[0]->sum;
        if(c[1]) sum += c[1]->sum;
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
	LinkCut(int N) : node(N) {}

	void link(int u, int v) { // add an edge (u, v)
		assert(!connected(u, v));
		makeRoot(&node[u]);
		node[u].pp = &node[v];
	}
	void cut(int u, int v) { // remove an edge (u, v)
		Node *x = &node[u], *top = &node[v];
		makeRoot(top); x->splay();
		assert(top == (x->pp ?: x->c[0]));
		if (x->pp) x->pp = 0;
		else {
			x->c[0] = top->p = 0;
			x->fix();
		}
	}
    void update(int u, int w){
        access(&node[u]);
        node[u].w = w;
        node[u].fix();
    }
	bool connected(int u, int v) { // are u, v in the same tree?
		Node* nu = access(&node[u])->first();
		return nu == access(&node[v])->first();
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
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        set<int> unused;
        LinkCut tree((n + 2) * 2);
        // 0 jump 1 lazy
        rep(i, 0, n){
            cin >> a[i]; a[i];
        }
        rep(i, 0, n + 1){
            unused.insert(i);
            tree.link(i * 2, i * 2 + 1); // jump to lazy of self
            tree.link(i * 2 + 1, (i + 1) * 2 + 1); // lazy to next lazy
        }
        int sink = (n + 1) * 2 + 1;
        tree.link((n + 1) * 2, (n + 1) * 2 + 1);
        // int mindex = n;
        vi ans;
        // cout << "num nodes is " << (n + 2) * 2 << endl;
        rep(i, 0, n){
            // cout << "on " << i << " " << a[i] << endl;
            // mindex = min(mindex, a[i]);
            while(sz(unused)){
                // cout << "loop interation" << endl;
                auto it = unused.lower_bound(a[i]);
                if(it == unused.begin()) break;
                it = prev(it);
                int val = *it;
                if(val + k < a[i]) break;
                // cout << "checking " << val << endl;
                // cout << "cut " << val << endl;
                tree.cut(val * 2 + 1, (val + 1) * 2 + 1);
                // cout << "did cut " << endl;
                tree.update(val * 2 + 1, 1);
                tree.link(val * 2 + 1, min(n, val + k) * 2);
                tree.makeRoot(&tree.node[sink]);
                // cout << "did link" << endl;
                unused.erase(val);
            }
            // tree.reroot(sink);
            tree.access(&tree.node[0]);
            tree.makeRoot(&tree.node[sink]);
            tree.access(&tree.node[0]);
            ans.pb(tree.node[0].sum);
            // cout << ans << " ";
            // cout << "finished " << i << " " << ans.back() << endl;
        }
        for(int i : ans) cout << i << " ";
        cout << endl;
    }
    
    return 0;
}
