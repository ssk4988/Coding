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

void solve(int cn) {
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m, -1));

    vvi dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    string dirs = "DRUL";
    rep(i,0, n){
        string s; cin >> s;
        rep(j, 0, m){
            if(s[j] == '?') continue;
            grid[i][j] = find(all(dirs), s[j]) - begin(dirs);
        }
    }
    rep(i, 0, n){
        rep(j, 0, m){
            rep(k, 0, 4){
                int i1 = i + dir[k][0], j1 = j + dir[k][1];
                if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                if((grid[i][j] == k || grid[i][j] == -1) && (grid[i1][j1] == (k+2)%4 || grid[i1][j1] == -1)){
                    grid[i][j] = k;
                    grid[i1][j1] = (k + 2) % 4;
                }
            }
        }
    }
    vvi cycles(n, vi(m));
    vvi state(n, vi(m));
    auto dfs = [&](int i, int j, auto &&dfs) -> bool {
        if(i < 0 || j < 0 || i >= n || j >= m) return false;
        if(state[i][j]){
            if(state[i][j] == 1) cycles[i][j] = true;
            return state[i][j] == 1;
        }
        state[i][j] = 1;
        int k = grid[i][j];
        int i1 = i + dir[k][0], j1 = j + dir[k][1];
        if(dfs(i1, j1, dfs)){
            cycles[i][j] = true;
            return true;
        }
        state[i][j] = 2;
        return false;
    };
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] != -1) dfs(i, j, dfs);
        }
    }

    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] != -1){
                continue;
            }
            rep(k, 0, 4){
                int i1 = i + dir[k][0], j1 = j + dir[k][1];
                if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                if(cycles[i1][j1]){
                    grid[i][j] = k;
                    break;
                }
            }
            if(grid[i][j] == -1) {
                grid[i][j] = 0;
            }
            dfs(i, j, dfs);
        }
    }
    int ans = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            ans += cycles[i][j];
        }
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve(cn);
    }
    
    return 0;
}
