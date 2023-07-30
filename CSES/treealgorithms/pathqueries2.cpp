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
const int maxn = 2e5 + 10;
vi adj[maxn];

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("avx2")

const ll inf = 1e16;
struct Node
{
	Node *l = 0, *r = 0;
	int lo, hi;
	ll mset = inf, val = -inf;
	Node(vl &v, int lo, int hi) : lo(lo), hi(hi)
	{
		if (lo + 1 < hi)
		{
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid);
			r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else
			val = v[lo];
	}
	ll query(int L, int R)
	{
		if (R <= lo || hi <= L)
			return -inf;
		if (L <= lo && hi <= R)
			return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x)
	{
		if (R <= lo || hi <= L)
			return;
		if (L <= lo && hi <= R)
			mset = val = x;
		else
		{
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push()
	{
		if (mset != inf)
			l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
	}
};

template <bool VALS_EDGES>
struct HLD
{
	int N, tim = 0;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(int n, vl &arr)
		: N(n), par(N, -1), siz(N, 1), depth(N),
		  rt(N), pos(N)
	{
		dfsSz(0);
		dfsHld(0);
		vl arr2(sz(arr));
		rep(i, 0, sz(pos)) arr2[pos[i]] = arr[i];
		tree = new Node(arr2, 0, N);
	}
	void dfsSz(int v)
	{
		if (par[v] != -1)
			adj[v].erase(find(all(adj[v]), par[v]));
		for (int &u : adj[v])
		{
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]])
				swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v)
	{
		pos[v] = tim++;
		for (int u : adj[v])
		{
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B>
	void process(int u, int v, B op)
	{
		for (; rt[u] != rt[v]; v = par[rt[v]])
		{
			if (depth[rt[u]] > depth[rt[v]])
				swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v])
			swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val)
	{
		process(u, v, [&](int l, int r)
				{ tree->set(l, r, val); });
	}
	ll queryPath(int u, int v)
	{ // Modify depending on problem
		ll res = -inf;
		process(u, v, [&](int l, int r)
				{ res = max(res, tree->query(l, r)); });
		return res;
	}
	int querySubtree(int v)
	{ // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n, q;
	cin >> n >> q;
	vl arr(n);
	rep(i, 0, n)
	{
		cin >> arr[i];
	}
	rep(i, 0, n - 1)
	{
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	HLD<0> hld(n, arr);
	rep(i, 0, q)
	{
		int t;
		cin >> t;
		if (t == 1)
		{
			int s, x;
			cin >> s >> x;
			s--;

			hld.modifyPath(s, s, x);
		}
		else
		{
			int a, b;
			cin >> a >> b;
			a--, b--;
			cout << hld.queryPath(a, b) << " ";
		}
	}
	cout << nL;

	return 0;
}
