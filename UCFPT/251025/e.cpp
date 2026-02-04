#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

/*
impossible - odd c
also 2 rows, all filled

if bottom row is less than half, then work inward in each row going upward
otherwise:
case where left/right fill blocks last one
fails only if half+1 in bottom row, left and right 2 occupied
up fill from side until get one more

ANY INSTANCE OF THIS is impossible
##C##
#.C.#
CC.CC

##C##
#C..#
CC.CC

##C##
#..C#
CC.CC




###.###
##..C##
#...C.#
CC...CC

###.###
##..C##
#.....#
CC.C.CC

how to cheese with flow?

final alg:
check odd c - impossible
dont code up explicitly - if two rows and all filled - impossible
if bottom row has less then half:
fill all bottom, work in each side on each upward row until good
else:
try both horizontal flips:
left fill bottom until success.
if this blocks last element, claim it unless it is also marked
if not solved, now upward fill cells until we get one more

write checker
if no solution, impossible

   

CC...CC
*/

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int m = 2*n-1;
    vector<string> grid(n);
    int c = 0;
    rep(i, 0, n) {
        cin >> grid[i];
        rep(j, 0, m) {
            if(grid[i][j] == 'C') c++;
        }
    }
    if(c % 2 == 1) {
        cout << "impossible\n";
        return 0;
    }
    int bottom = 0;
    rep(i, 0, m) {
        if(grid[n-1][i] == 'C') bottom++;
    }
    int half = c/2;
    auto check = [&](vector<string> &ans) -> bool {
        // cerr << "checking:" << endl;
        // rep(i,0,n) cerr << ans[i] << endl;
        int a = 0;
        rep(i, 0, n) {
            rep(j, 0, m) {
                a += grid[i][j] == 'C' && ans[i][j] == 'A';
            }
        }
        if(a != half) return false;
        vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
        int comps = 0;
        vvi vis(n, vi(m));
        auto dfs = [&](int r, int c, char t, auto &&dfs) -> void {
            if(vis[r][c] || ans[r][c] != t) return;
            vis[r][c] = 1;
            rep(k, 0, 4) {
                int r1 = r + dr[k], c1 = c + dc[k];
                if(min(r1, c1) < 0 || r1 >= n || c1 >= m) continue;
                dfs(r1, c1, t, dfs);
            }
        };
        rep(i, 0, n) {
            rep(j, 0, m) {
                if(vis[i][j]) continue;
                comps++;
                dfs(i, j, ans[i][j], dfs);
            }
        }
        return comps == 4;
    };
    if(bottom <= half) {
        vector<string> ans(n, string(m, '#'));
        vi ord;
        rep(i, 0, n) ord.push_back(i), ord.push_back(m-1-i);
        ord.pop_back();
        int a = bottom;
        rep(i, 0, m) ans[n-1][i] = 'A';
        for(int i = n-2; i >= 0 && a < half; i--) {
            for(int j : ord) {
                if(grid[i][j] == '#') continue;
                ans[i][j] = 'A';
                a += grid[i][j] == 'C';
                if(a == half) break;
            }
        }
        rep(i, 0, n) {
            rep(j, 0, m) if(ans[i][j] != 'A' && grid[i][j] != '#') ans[i][j] = 'B';
        }
        assert(check(ans));
        rep(i, 0, n) {
            cout << ans[i] << "\n";
        }
        return 0;
    }
    rep(rev, 0, 2) {
        vector<string> ans(n, string(m, '#'));
        int a = 0, bot = 0;
        while(a < half) {
            a += grid[n-1][bot] == 'C';
            ans[n-1][bot] = 'A';
            bot++;
        }
        if(bot == m-1 && grid[n-1][bot] != 'C') {
            // cerr << "add onto end" << endl;
            ans[n-1][bot] = 'A';
            bot++;
        } else if(bot == m-1) {
            // cerr << "weird case" << endl;
            ans[n-1][bot-1] = '#';
            a--;
            rep(j, 0, m) {
                if(a == half) break;
                for(int i = n-2; i >= 0; i--) {
                    if(grid[i][j] == '#') break;
                    ans[i][j] = 'A';
                    a += grid[i][j] == 'C';
                    if(a == half) break;
                }
            }
        }
        rep(i, 0, n) {
            rep(j, 0, m) if(ans[i][j] != 'A' && grid[i][j] != '#') ans[i][j] = 'B';
        }
        if(check(ans)) {
            if(rev) {
                rep(i, 0, n) reverse(all(ans[i]));
            }
            rep(i, 0, n) cout << ans[i] << "\n";
            return 0;
        }


        rep(i, 0, n) {
            reverse(all(grid[i]));
        }
    }
    cout << "impossible\n";

    return 0;
}
