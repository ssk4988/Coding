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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vvi grid(n, vi(m));
        vector<vii> loc(n*m);
        rep(i, 0, n) {
            rep(j, 0, m) {
                cin >> grid[i][j]; grid[i][j]--;
                loc[grid[i][j]].pb({i, j});
            }
        }
        vi dist(2*n*m, -1);
        priority_queue<pii, vii, greater<>> q;
        q.push({0, 0});
        vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
        while(sz(q)) {
            auto [d, id] = q.top(); q.pop();
            if(dist[id] != -1) continue;
            dist[id] = d;
            if(id < n*m) {
                int i = id / m, j = id % m;
                rep(k, 0, 4) {
                    int i1 = i + dr[k], j1 = j + dc[k];
                    if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
                    q.push({d+1, i1*m+j1});
                }
                q.push({d+1, n*m+grid[i][j]});
            } else {
                for(auto [i, j] : loc[id - n*m]) {
                    q.push({d, i*m+j});
                }
            }
        }
        cout << dist[n*m-1] << "\n";
    }
    
    return 0;
}
