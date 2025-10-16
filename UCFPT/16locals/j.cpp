#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

// binary search answer
// then dijkstra
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
        vvi grid(n, vi(m));
        rep(i, 0, n) {
            rep(j, 0, m) cin >> grid[i][j];
        }
        auto test = [&](int minh) -> bool {
            using state = array<int, 3>;
            vvi dist(n, vi(m, -1));
            queue<state> pq;
            pq.push({0, 0, 0});
            while(sz(pq)) {
                auto [d, i, j] = pq.front(); pq.pop();
                if(grid[i][j] - d < minh) continue;
                if(dist[i][j] != -1) continue;
                dist[i][j] = d;
                rep(k, 0, 4) {
                    int i1 = i + dr[k], j1 = j + dc[k];
                    if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
                    pq.push({d+1, i1, j1});
                }
            }
            // cerr << "test " << minh << " " << (dist[n-1][m-1] != -1) << endl;
            if(dist[n-1][m-1] == -1) return false;
            return true;
        };
        int ans = 0;
        for(int dif = 1 << 29; dif; dif /= 2) {
            if(test(ans + dif)) ans += dif;
        }
        if(ans == 0) cout << "impossible\n";
        else cout << ans << "\n";
    }


    return 0;
}
