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

int n;
vector<array<int, 3>> a;

struct node {
	int val, prior, sz = 1;
	node *left = nullptr, *right = nullptr;
	node(int val = 0): val(val), prior(rand()) {}
};

int getSz(node *cur) { return cur ? cur->sz : 0; }
void recalc(node *cur) { cur->sz = getSz(cur->left) + getSz(cur->right) + 1; }

pair<node*, node*> split(node *cur, int v) {
	if(!cur) return {nullptr, nullptr};
	node *left, *right;
	if(getSz(cur->left) >= v) {
		right = cur;
		auto [L, R] = split(cur->left, v);
		left = L, right->left = R;
		recalc(right);
	}
	else {
		left = cur;
		auto [L, R] = split(cur->right, v - getSz(cur->left) - 1);
		left->right = L, right = R;
		recalc(left);
	} 
	return {left, right};
}

node* merge(node *t1, node *t2) {
	if(!t1 || !t2) return t1 ? t1 : t2;
	node *res;
	if(t1->prior > t2->prior) {
		res = t1;
		res->right = merge(t1->right, t2);
	}
	else {
		res = t2;
		res->left = merge(t1, t2->left);
	}
	recalc(res);
	return res;
}

// i beats j
bool beat(int i, int j) {
    int c = 0;
    rep(k, 0, 3) c += a[i][k] > a[j][k];
    return c >= 2;
}

int lastBeat(node *cur, int v) {
    if(!cur) return 0;
    if(beat(v, cur->val)) {
        return getSz(cur->left) + 1 + lastBeat(cur->right, v);
    }
    return lastBeat(cur->left, v);
}

void dfs(node *cur) {
    if(!cur) return;
    dfs(cur->left);
    cerr << cur->val << ",";
    dfs(cur->right);
}

struct Node {
    int lo, hi;
    vii val;
    Node *l = 0, *r = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi-lo)/2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void add(int L, int R, int idx, int y) {
        if(R <= lo || hi <= L) return;
        val.push_back({y, idx});
        // cerr << "insert y=" << y << " idx=" << idx << " on segment " << lo << "," << hi << endl;
        if(L <= lo && hi <= R) {
            return;
        }
        l->add(L, R, idx, y), r->add(L, R, idx, y);
    }
    void fix() {
        sort(all(val));
        if(l)
        l->fix(), r->fix();
    }
    void query(int L, int R, int y, vi &res) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            while(sz(val)) {
                auto [vf, vs] = val.back();
                if(vf < y) break;
                // cerr << "adding idx=" << vs << " idxy=" << vf << " for " << y << endl;
                res.push_back(vs);
                val.pop_back();
            }
            return;
        }
        l->query(L, R, y, res);
        r->query(L, R, y, res);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n;
    n++;
    a.resize(n);
    rep(i, 0, n) {
        rep(j, 0, 3) cin >> a[i][j];
    }
    vector<Node> trees;
    rep(t, 0, 3) trees.push_back(Node(0, n));
    vii indices = {
        {0, 1},
        {1, 2},
        {2, 0}
    };
    rep(t, 0, 3) {
        auto [f, s] = indices[t];
        rep(i, 0, n) {
            // cerr << "add " << t << " " << a[i][f] << " " << a[i][s] << " " << i << endl;
            trees[t].add(a[i][f], a[i][f]+1, i, a[i][s]);
        }
        trees[t].fix();
    }
    vi perm;
    vi used(n);
    used[0] = 1;
    node *treap = new node(0);
    while(treap) {
        // cerr << "treap: ";
        // dfs(treap);
        // cerr << endl;
        vi upd;
        int cur;
        {
            node *left = treap;
            while(left->left) left = left->left;
            cur = left->val;
        }
        rep(t, 0, 3) {
            auto [f, s] = indices[t];
            // cerr << "query: " << t << " beating " << cur << " " << a[cur][f] << " " << a[cur][s] << endl;
            trees[t].query(a[cur][f], n, a[cur][s], upd);
            // for(int ins : upd) cerr << t << " " << ins << " " << cur << endl;
        }
        
        for(int ins : upd) {
            if(used[ins]) continue;
            used[ins] = true;
            // cerr << ins << " beats " << cur << endl;
            assert(beat(ins, cur));
            int idx = lastBeat(treap, ins);
            assert(idx >= 1);
            auto [L, R] = split(treap, idx);
            treap = merge(L, merge(new node(ins), R));
        }
        auto [L, R] = split(treap, 1);
        perm.push_back(L->val);
        treap = R;
    }
    int w = 0;
    rep(i, 0, n) if(!used[i]) {
        // cerr << "adding in " << i << endl;
        perm.pb(i);
    }
    assert(sz(perm) == n);
    bool works = true;
    rep(i, 1, sz(perm)) {
        works = works && beat(perm[i], perm[i-1]);
        w += works;
    }
    cout << w << "\n";
    rep(i, 1, sz(perm)){
        cout << perm[i] << " ";
    }
    cout << "\n";
    return 0;
}
