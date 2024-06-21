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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vi dx{1, -1, 0, 0, 0, 0}, dy{0, 0, 1, -1, 0, 0}, dz{0, 0, 0, 0, 1, -1};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vvi> grid(n, vvi(n, vi(n)));
    rep(i, 0, n){
        rep(j, 0, n){
            rep(k, 0, n){
                cin >> grid[i][j][k];
            }
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        vector<vvi> test(grid);
        int x, y, z; cin >> x >> y >> z;
        int ans = 0;
        auto dfs = [&](int x, int y, int z, auto &&dfs)->void {
            if(min({x, y, z}) < 0 || max({x, y, z}) >= n || test[x][y][z] == 0) return;
            test[x][y][z] = 0;
            ans++;
            rep(t, 0, 6){
                int x1 = x + dx[t], y1 = y + dy[t], z1 = z + dz[t];
                dfs(x1, y1, z1, dfs);
            }
        };
        dfs(x, y, z, dfs);
        cout << "Simulation #" << (cn+1) << ", volume cleared is " << ans << " cubic feet.\n\n";
    }
    
    return 0;
}
