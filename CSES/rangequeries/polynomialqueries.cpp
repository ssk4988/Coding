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

const ll inf = 1e9;

ll tri(ll x){
	if(x <= 1) return 1;
	return (x + 1) * x / 2;
}

struct Node
{
	Node *l = 0, *r = 0;
	ll lo, hi, mid;
	ll lzconst = 0, lzslope = 0, initial = 0;
	Node(vl &v, ll lo, ll hi) : lo(lo), hi(hi)
	{
		if (lo + 1 < hi)
		{
			mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid);
			r = new Node(v, mid, hi);
			initial = l->initial + r->initial;
		}
		else
			initial = v[lo];
	}
	ll query(ll L, ll R)
	{
		// cout << "segment [" << lo << ", " << hi << "), initial=" << initial << nL;
		if (R <= lo || hi <= L)
			return 0;
		if (L <= lo && hi <= R)
		{
			// ll resval = initial + constant * (hi - lo) + slope * (hi - lo - 1) * (hi - lo) / 2;
			ll resval = initial;
			// cout << "segment [" << lo << ", " << hi << "), contributes " << resval << " with initial=" << initial << nL;
			return resval;
		}
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(ll L, ll R)
	{
		if (R <= lo || hi <= L)
			return;
		if (L <= lo && hi <= R)
		{
			// cout << "on segment [" << lo << ", " << hi << "), adding " << (lo - L) << " to const and " << 1 << " to slope, initial from " << initial;
			initial += (lo - L) * (hi - lo);
			lzconst += (lo - L);
			initial += 1 * tri(hi - lo);
			lzslope += 1;
			// cout << " to " << initial << nL;
		}
		else
		{
			push(), l->add(L, R), r->add(L, R);
			initial = l->initial + r->initial;
		}
	}
	void push()
	{
		if(lo + 1 == hi) return;
		if (lzslope != 0)
		{
			l->lzslope += lzslope;
			r->lzslope += lzslope;
			r->lzconst += (r->lo - lo) * lzslope;
			r->initial += (r->lo - lo) * lzslope * (r->hi - r->lo);
			l->initial += lzslope * tri(l->hi - l->lo);
			r->initial += lzslope * tri(r->hi - r->lo);

			lzslope = 0;
		}
		if (lzconst != 0)
		{
			// cout << "on segment [" << lo << ", " << hi << "), pushing const of " << (lzconst + r->lo - lo) << " to right and " << lzconst << " to left" << nL;
			l->lzconst += lzconst;
			r->lzconst += lzconst;
			l->initial += lzconst * (l->hi - l->lo);
			r->initial += lzconst * (r->hi - r->lo);
			lzconst = 0;
		}
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n, q;
	cin >> n >> q;
	vl a(n);
	rep(i, 0, n)
	{
		cin >> a[i];
	}
	Node *tree = new Node(a, 0, n);
	rep(i, 0, q)
	{
		int t;
		cin >> t;
		if (t == 1)
		{
			int a, b;
			cin >> a >> b;
			a--, b--;
			tree->add(a, b + 1);
		}
		else
		{
			int a, b;
			cin >> a >> b;
			a--, b--;
			cout << tree->query(a, b + 1) << nL;
		}
	}

	return 0;
}
