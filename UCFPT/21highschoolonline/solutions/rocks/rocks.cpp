#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 16;
const ll oo = 1e12;
ll dp[N][2 * N][1 << N], adj[N + 2][N + 2];
bool wall[N], concert[N];
ll t, a, b, n, m;

// returns the minimum amount of time required to achieve this score
// from this node having visited a bitmask already
ll go(int u, int score, int mask) {

	if (score < 0)
		return oo;

	if (u == n + 1) // we're at seattle
		return score == 0 ? 0 : oo;

	ll& val = dp[u][score][mask];

	if (val != -1)	
		return val;

	ll ans = oo;

	for (int v = 0; v <= n + 1; v++) {
		// skip if no edge or if we've already been here
		if (u == v || adj[u][v] == -1 || (mask & (1 << v)))
			continue;

		// iterate on the choices to visit a wall/concert or not
		for (int dw = 0; dw <= wall[u]; dw++)
			for (int dc = 0; dc <= concert[u]; dc++) {
				ll here = go(v, score - dw - dc, mask | (1 << u));
				ans = min(ans, adj[u][v] + a * dw + b * dc + here);
			}
	}

	return val = ans;
}

void solve() {

	memset(dp, -1, sizeof(dp));
	memset(adj, -1, sizeof(adj));

	cin >> t >> a >> b >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> wall[i] >> concert[i];

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		adj[u][v] = adj[v][u] = w;
	}

	int ans = -1;

	// for each score, if we can achieve it in time, update answer
	for (int score = 0; score <= 2 * n; score++)
		if (go(0, score, 0) <= t)
			ans = max(ans, score);

	if (ans == -1)
		cout << "Book a flight!\n";
	else
		cout << ans << '\n';
}

int main() {
	int t;
	cin >> t;
	while (t--)
		solve();
}
