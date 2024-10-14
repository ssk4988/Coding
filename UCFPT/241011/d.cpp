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
    int n,m; cin >> n >> m; n += 2, m += 2;
    int k; cin >> k;
    vvi grid(n, vi(m));
    vi res(k);
    int vertices = 0;
    int edges = 0;
    auto is_vertex = [&](int i, int j) -> int {
        if(i == 0 || j == 0 || i == n || j == m) return 1;
        int black = 0;
        for(int x : {0, -1}) {
            for(int y : {0, -1}) black += grid[i-x][j-y];
        }
        return black != 0 && black != 4;
    };
    // d=0 = vertical edge, 1 = horizontal edge
    auto is_edge = [&](int i, int j, int d) -> int {
        if(d == 0 && i == n || d == 1 && j == m) return 0; // off grid
        if(d == 0 && (j == 0 || j == m) || d == 1 && (i == 0 || i == n)) return 1;
        if(d == 0) {
            return grid[i][j] != grid[i][j-1];
        }
        return grid[i][j] != grid[i-1][j];
    };
    rep(i, 0, n+1){
        rep(j, 0, m+1) {
            
        }
    }
    rep(q, 0, k) {
        int r, c; cin >> r >> c;
        grid[r][c] = 1;
        int cnt = 0;
        rep(i, -1, 2){
            rep(j, -1, 2) cnt += grid[r+i][c+j];
        }
        if(cnt == 9) {
            grid[r][c] = 0;
            continue;
        }
        int pv = vertices, pe = edges;
    }
    
    return 0;
}
