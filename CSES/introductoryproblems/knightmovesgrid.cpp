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
    int n; cin >> n;
    vvi dist(n, vi(n, -1));
    vi dr{1, 1, -1, -1, 2, 2, -2, -2};
    vi dc{2, -2, 2, -2, 1, -1, 1, -1};
    queue<array<int, 3>> q;
    q.push(array<int, 3>{0, 0, 0});
    while(sz(q)) {
        auto [d, r, c] = q.front(); q.pop();
        if(dist[r][c] != -1) continue;
        dist[r][c] = d;
        rep(i, 0, sz(dr)) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if(min(r1, c1) < 0 || max(r1, c1) >= n) continue;
            q.push({d+1, r1, c1});
        }
    }
    rep(i, 0, n) {
        rep(j, 0, n) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
