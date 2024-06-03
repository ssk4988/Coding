#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, sx, sy; cin >> n >> sx >> sy;
    vvi grid(n+5, vi(n+5));
    vector<set<int>> rows(n+5), cols(n+5);
    auto visit = [&](int x, int y)->void {
        if(grid[x][y]) return;
        grid[x][y] = 1;
        rows[x].insert(y);
        cols[y].insert(x);
    };
    auto relax = [&](int x, int y) -> void {
        rows[x].erase(y);
        cols[y].erase(x);
        visit(x+1, y);
        visit(x, y+1);
    };
    visit(0, 0);
    rep(i, 0, n){
        int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
        x1 -= sx, x2 -= sx;
        y1 -= sy, y2 -= sy;
        x1 = max(x1, 0), y1 = max(y1, 0);
        x2 = min(x2, n), y2 = min(y2, n);
        vii qs;
        rep(tx, x1, x2+1){
            auto it = rows[tx].lower_bound(y1);
            while(it != rows[tx].end() && *it <= y2) {
                qs.pb({tx, *it});
                it = next(it);
            }
        }
        rep(ty, y1, y2+1){
            auto it = cols[ty].lower_bound(x1);
            while(it != cols[ty].end() && *it <= x2){
                qs.pb({*it, ty});
                it = next(it);
            }
        }
        for(auto [x, y] : qs) relax(x, y);
    }
    int ans = 0;
    rep(i,0,n+1){
        rep(j,0,n+1) if(grid[i][j]) ans = max(ans, i+j);
    }
    cout << ans << "\n";
    return 0;
}
