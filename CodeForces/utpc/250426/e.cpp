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
    
    int n, qs; cin >> n >> qs;
    vector<string> grid(n);
    using a3 = array<int, 3>;
    queue<a3> q;
    rep(i, 0, n) {
        cin >> grid[i];
        rep(j, 0, n) {
            if(grid[i][j] == 'E') {
                q.push({1, i, j});
            }
        }
    }
    vvi dist(n, vi(n, -1));
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    while(sz(q)) {
        auto [d_u, r, c] = q.front(); q.pop();
        if(dist[r][c] != -1) continue;
        dist[r][c] = d_u;
        rep(k, 0, 4) {
            int r1 = r + dr[k], c1 = c + dc[k];
            if(min(r1, c1) < 0 || max(r1, c1) >= n) continue;
            if(grid[r1][c1] == '#') continue;
            q.push({d_u+1, r1, c1});
        }
    }
    vi cnt(n * n + 10);
    ll empty = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if(grid[i][j] == '.') empty++;
            if(dist[i][j] > 1) {
                cnt[dist[i][j]]++;
            }
            // cerr << dist[i][j] << " ";
        }
        // cerr << endl;
    }
    rep(i, 1, sz(cnt)) {
        cnt[i] += cnt[i-1];
    }

    ll ways = ll(empty);
    // cerr << empty << endl;
    rep(qid, 0, qs) {
        int bread; cin >> bread;
        ll good = cnt[bread];
        ll goodways = good;
        cout << fixed << setprecision(10) << ld(goodways) / ways << "\n";
    }

    return 0;
}
