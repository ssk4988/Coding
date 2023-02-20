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

const int MN = 2e5 + 20;
int n, k1, k2;
ll ans = 0;

int maxDepth = 0;
vector<int> a[MN];
bool r[MN]; // removed
int s[MN];	// subtree size
ll bit[MN];

void update(int index, ll change)
{
	index++;
	while (index < MN)
	{
		bit[index] += change;
		index += index & -index;
	}
}

ll query(int index)
{
	index++;
	ll sum = 0;
	while (index > 0)
	{
		sum += bit[index];
		index -= index & -index;
	}
	return sum;
}

ll query(int l, int r)
{
	return query(r) - query(l - 1);
}

int dfs(int n, int p = 0)
{
	s[n] = 1;
	for (int x : a[n])
		if (x != p && !r[x])
			s[n] += dfs(x, n);
	return s[n];
}
int get_centroid(int n, int ms, int p = 0) // n = node, ms = size of tree, p = parent
{
	for (int x : a[n])
		if (x != p && !r[x])
			if (s[x] * 2 > ms)
				return get_centroid(x, ms, n);
	return n;
}
void dfs2(int cur, int p, int dist, bool add)
{
	if (r[cur] || dist > k2)
		return;
	maxDepth = max(dist, maxDepth);
	if(add) update(dist, 1);
	else ans += query(max(0, k1 - dist), k2 - dist);
	for (int i : a[cur])
	{
		if (!r[i] && i != p)
		{
			dfs2(i, cur, dist + 1, add);
		}
	}
}
void centroid(int n = 1)
{
	int C = get_centroid(n, dfs(n));

	// do something

	r[C] = 1;
	
	for (int i = 0; i < a[C].size(); i++)
	{
		int x = a[C][i];
		dfs2(x, C, 1, false);
		dfs2(x, C, 1, true);
	}
	for (int i = 1; i <= maxDepth; i++) update(i, -query(i, i));
	for (int x : a[C])
		if (!r[x])
		{
			centroid(x);
		}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	cin >> n >> k1 >> k2;
	update(0, 1);
	rep(i, 0, n - 1)
	{
		int x, y;
		cin >> x >> y;
		a[x].pb(y);
		a[y].pb(x);
	}
	centroid();
	cout << ans << nL;
	return 0;
}
