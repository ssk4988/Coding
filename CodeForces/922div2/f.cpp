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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
	int n, k; cin >> n >> k;
	vi par(n), depth(n), deep(n);
	vvi child(n);
	rep(i, 1, n){
		cin >> par[i]; par[i]--;
		child[par[i]].pb(i);
	}
	priority_queue<int> pq;
	auto dfs = [&](int u, auto &&dfs) -> void {
		deep[u] = depth[u];
		for(int v : child[u]){
			depth[v] = depth[u] + 1;
			dfs(v, dfs);
			deep[u] = max(deep[u], deep[v]);
		}
		sort(all(child[u]), [&](int a, int b) -> bool {return deep[a] < deep[b]; });
		rep(i, 0, sz(child[u]) - 1){
			pq.push(deep[child[u][i]] - 2 * depth[u]);
		}
	};
	dfs(0, dfs);
	ll ans = 2 * (n - 1) - deep[0];
	while(k && sz(pq)){
		int x = pq.top(); pq.pop();
		if(x <= 0) break;
		ans -= x;
		k--;
	}
	cout << ans << nL;

    
    return 0;
}
