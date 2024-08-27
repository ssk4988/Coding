#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    vector<string> grid(r);
    pii bon, cly, tar;
    rep(i, 0, r){
        cin >> grid[i];
        rep(j, 0, c){
            if(grid[i][j] == 'B') bon = {i, j};
            else if(grid[i][j] == 'C') cly = {i, j};
            else if(grid[i][j] == 'F') tar = {i, j};
            // else 
        }
    }
    vii dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    auto calc = [&](int sr, int sc, vector<string> g) -> pair<vector<vii>, vvi> {
        vector<vii> prv(r, vii(c, {-1, -1}));
        vvi dist(r, vi(c, -1));
        queue<array<int, 5>> q;
        q.push({0, sr, sc, -1, -1});
        while(!q.empty()){
            auto [d, i, j, pi, pj] = q.front(); q.pop();
            if(!(0 <= i && i < r && 0 <= j && j < c)) continue;
            if(g[i][j] == 'x' || dist[i][j] != -1) {
                continue;
            }
            dist[i][j] = d;
            prv[i][j] = {pi, pj};
            for(auto [dr, dc] : dir){
                q.push({d+1, i+dr, j+dc, i, j});
            }
        }
        return {prv, dist};
    };
    int ans = 1e9;
    for(auto [first, second] : vector<pair<pii, pii>>{pair<pii, pii>{bon, cly}, pair<pii, pii>{cly, bon}}){
        auto [prv, dist] = calc(first.first, first.second, grid);
        cout << "d1: " << first.first << " " << first.second << " " << dist[tar.first][tar.second]  << "\n";
        rep(i, 0, r){
            rep(j, 0, c){
                cout << dist[i][j] << " ";
            }
            cout << "\n";
        }
        if(dist[tar.first][tar.second] == -1) continue;
        auto [curr, curc] = prv[tar.first][tar.second];
        auto g(grid);
        while(curr != -1){
            g[curr][curc] = 'x';
            auto [prvr, prvc] = prv[curr][curc];
            curr = prvr, curc = prvc;
        }
        auto [prv1, dist1] = calc(second.first, second.second, g);
        if(dist1[tar.first][tar.second] == -1) continue;
        ans = min(ans, dist[tar.first][tar.second] + dist1[tar.first][tar.second]);
    }
    if(ans == 1e9) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}
