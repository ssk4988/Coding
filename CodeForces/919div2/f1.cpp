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
    
    int n, m, q; cin >> n >> m >> q;
    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }
    const int inf = 1e9;
    vvi dist(n, vi(m, inf));
    {
        queue<array<int, 3>> pq;
        rep(i, 0, n) {
            rep(j, 0, m) {
                if(grid[i][j] == 'v') {
                    pq.push({i, j, 0});
                }
            }
        }
        while(sz(pq)) {
            auto [i, j, d] = pq.front(); pq.pop();
            if(dist[i][j] != inf) continue;
            dist[i][j] = d;
            if(i) pq.push({i-1, j, d+1});
            if(i+1<n) pq.push({i+1, j, d+1});
            if(j) pq.push({i, j-1, d+1});
            if(j+1<m) pq.push({i, j+1, d+1});
        }
    }
    rep(i, 0, q) {
        int sr, sc; cin >> sr >> sc; sr--, sc--;
        // whether if stay dist of from away from volcano, can surround it
        auto test = [&](int from) -> bool {
            // if(dist[sr][sc] < from) return false;
            vvi block(n, vi(m));
            queue<pii> pq;
            pq.push({sr, sc});
            while(sz(pq)) {
                auto [i, j] = pq.front(); pq.pop();
                if(grid[i][j] == '#' || block[i][j] || dist[i][j] < from) continue;
                block[i][j] = 1;
                if(i) pq.push({i-1, j});
                if(i+1<n) pq.push({i+1, j});
                if(j) pq.push({i, j-1});
                if(j+1<m) pq.push({i, j+1});
            }
            vvi reach(n, vi(m));
            rep(i, 0, n) {
                rep(j, 0, m) {
                    if(grid[i][j] == '#' && !block[i][j]) pq.push({i, j});
                }
            }
            while(sz(pq)) {
                auto [i, j] = pq.front(); pq.pop();
                reach[i][j] = 1;
                rep(i1, i-1, i+2) {
                    rep(j1, j-1, j+2) {
                        if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                        if(block[i1][j1] || reach[i1][j1]) continue;
                        reach[i1][j1] = true;
                        pq.push({i1, j1});
                    }
                }
            }
            bool works = true;
            rep(i, 0,n) {
                rep(j, 0, m) if(reach[i][j] && (i == 0 || j == 0 || i+1 == n || j+1 == m)) works = false;
            }
            return works;
        };
        int ans = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            if(test(ans+dif)) ans += dif;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
