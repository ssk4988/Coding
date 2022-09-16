#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int size(int x) { return -e[find(x)]; }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

long double distance(pll a, pll b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(10);
	int n; cin >> n;
	vector<pll> points(n);
	for (auto &[x, y] : points) cin >> x >> y;
	int q; cin >> q;
	vector<tuple<int, int, long double>> edges;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			edges.emplace_back(i, j, distance(points[i], points[j]));
		}
	} 
	sort(all(edges), [](tuple<int, int, long double> a, tuple<int, int, long double> b) {
		return get<2>(a) < get<2>(b);
	});	
	UF dsu(n);
	vector<vector<pair<int, long double>>> adj(n);
	for (auto [u, v, weight]: edges) {
		if (dsu.join(u, v)) {
			adj[u].emplace_back(v, weight);
			adj[v].emplace_back(u, weight);
		}
	}
	vector<vector<long double>> maxQueries(n, vector<long double>(n));
	auto dfs = [&](int u, int par, int start, long double max_so_far, auto && dfs) -> void {
		maxQueries[u][start] = max_so_far;
		maxQueries[start][u] = max_so_far;
		for (auto [v, weight]: adj[u]) if (v != par)
			dfs(v, u, start, max(max_so_far, weight), dfs);
	};

	for (int i = 0; i < n; i++) {
		dfs(i, i, i, 0, dfs);
	}
	
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b; a--; b--;
		cout << maxQueries[a][b] << "\n";
	}
}