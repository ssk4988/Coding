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
int n, k;
ll ans = 0;
 
vector<int> a[MN];
map<int, ll> dep[MN];
bool r[MN]; // removed
int s[MN];	// subtree size
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
void dfs2(unordered_map<int, ll> &freq, int cur, int p, int dist)
{
	if (r[cur])
		return;
	freq[dist]++;
	for (int i : a[cur])
	{
		if (!r[i] && i != p)
		{
			dfs2(freq, i, cur, dist + 1);
		}
	}
}
int centroid(int n = 1)
{
	int C = get_centroid(n, dfs(n));
 
	// do something
 
	// r[C] = 1;
	// unordered_map<int, ll> prev;
	// prev[0] = 1;
	// for (int i = 0; i < a[C].size(); i++)
	// {
	// 	int x = a[C][i];
	// 	unordered_map<int, ll> cur;
	// 	dfs2(cur, x, C, 1);
	// 	for (auto &p : prev)
	// 	{
	// 		if (cur.find(k - p.f) != cur.end())
	// 		{
	// 			ans += p.s * cur[k - p.f];
	// 		}
	// 	}
	// 	for (auto &p : prev)
	// 	{
	// 		cur[p.f] += p.s;
	// 	}
	// 	prev = cur;
	// }
 
	// vi childC;
	// for (int x : a[C])
	// 	if (!r[x])
	// 	{
	// 		childC.pb(centroid(x));
	// 	}
	return C;
}
 
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	cin >> n;
	rep(i, 0, n - 1)
	{
		int x, y;
		cin >> x >> y;
		a[x].pb(y);
		a[y].pb(x);
	}
	
	cout << (centroid()) << nL;
	return 0;
}