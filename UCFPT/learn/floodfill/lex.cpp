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

vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        rep(i, 0, n) cin >> grid[i];
        auto dfs = [&](int r, int c, auto &&dfs) -> void {
            if(r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == '.') return;
            grid[r][c] = '.';
            rep(t, 0, 4){
                dfs(r + dr[t], c + dc[t], dfs);
            }
        };
        int cnt = 0, cnt1 = 0;
        rep(i, 0, n){
            rep(j, 0, m){
                cnt += grid[i][j] == '.';
            }
        }
        rep(i, 0, n){
            rep(j, 0, m){
                if(grid[i][j] == 'X') dfs(i, j, dfs);
            }
        }
        rep(i, 0, n){
            rep(j, 0, m){
                cnt1 += grid[i][j] == '.';
            }
        }
        cout << (5 * (cnt1 - cnt)) << "\n";
    }
    
    return 0;
}
