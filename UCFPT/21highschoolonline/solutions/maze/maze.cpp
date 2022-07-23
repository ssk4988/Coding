#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define rep(a, b, c) for (int a = b; a < c; a++)
#define sz(x) (int)x.size()

using namespace std;
using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;

const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

void solve() {
	int n, m;
	cin >> n >> m;

	vector<string> mat(n);
	vector<vi> adj(n*m);
	for (int i = 0; i < n; i++)
		cin >> mat[i];

	vi bad(n*m, 0);

	int want = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (mat[i][j] == '*') {
				want = m*i + j;
				mat[i][j] = '9';
			}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] != 'G')
				continue;

			bad[m*i + j] = 1;

			for (int k = 0; k < 4; k++) {
				int x = i + DX[k];
				int y = j + DY[k];

				if (x < 0 || y < 0 || x >= n || y >= m)
					continue;

				bad[m*x + y] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!isdigit(mat[i][j]))
				continue;

			if (bad[m*i + j])
				continue;

			for (int k = 0; k < 4; k++) {
				int x = i + DX[k];
				int y = j + DY[k];

				if (x < 0 || y < 0 || x >= n || y >= m)
					continue;

				if (!isdigit(mat[x][y]) || bad[m*x + y])
					continue;

				if (abs(mat[i][j] - mat[x][y]) <= 1) {
					adj[m*i + j].push_back(m*x + y);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] != 'P' && mat[i][j] != 'E')
				continue;

			if (bad[m*i + j])
				continue;

			for (int k1 = 0; k1 < 4; k1++) {
				int x1 = i + DX[k1];
				int y1 = j + DY[k1];

				if (x1 < 0 || y1 < 0 || x1 >= n || y1 >= m)
					continue;

				if (!isdigit(mat[x1][y1]) || bad[m*x1 + y1])
					continue;
				
				for (int k2 = 0; k2 < 4; k2++) {
					if (k1 == k2)
						continue;

					int x2 = i + DX[k2];
					int y2 = j + DY[k2];

					if (x2 < 0 || y2 < 0 || x2 >= n || y2 >= m)
						continue;

					if (!isdigit(mat[x2][y2]) || bad[m*x2 + y2])
						continue;

					if (mat[x1][y1] > mat[x2][y2] || mat[i][j] == 'E')
						adj[m*x1 + y1].push_back(m*x2 + y2);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] != 'F' && mat[i][j] != 'E')
				continue;

			if (bad[m*i + j])
				continue;

			for (int k1 = 0; k1 < 4; k1++) {
				int x1 = i + DX[k1];
				int y1 = j + DY[k1];

				if (x1 < 0 || y1 < 0 || x1 >= n || y1 >= m)
					continue;

				if (!isdigit(mat[x1][y1]) || bad[m*x1 + y1])
					continue;

				
				for (int k2 = 0; k2 < 4; k2++) {
					if (k1 == k2)
						continue;

					int x2 = i + DX[k2];
					int y2 = j + DY[k2];

					if (x2 < 0 || y2 < 0 || x2 >= n || y2 >= m)
						continue;

					if (!isdigit(mat[x2][y2]) || bad[m*x2 + y2])
						continue;

					if (mat[x1][y1] < mat[x2][y2] || mat[i][j] == 'E')
						adj[m*x1 + y1].push_back(m*x2 + y2);
				}
			}
		}
	}

	vi dist(n*m, -1);
	queue<int> q;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 || i == n-1 || j == 0 || j == m-1) {
				if (mat[i][j] == '1' && !bad[m*i + j]) {

					dist[m*i + j] = 0;
					q.push(m*i + j);
				}
			}
		}
	}

	while (!q.empty()) {
		int u = q.front(); q.pop();

		if (u == want) {
			cout << "You've got this!\n";
			return;
		}

		for (int v : adj[u])
			if (dist[v] == -1 && !bad[v])
				dist[v] = dist[u] + 1, q.push(v);
	}

	cout << "Find another way\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int t; cin >> t; while (t--)
	solve();

	return 0;
}
