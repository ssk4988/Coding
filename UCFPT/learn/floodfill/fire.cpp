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

vi dr{1, 1, 1, 0, -1, -1, -1, 0}, dc{1, 0, -1, -1, -1, 0, 1, 1};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        rep(i, 0, n){
            cin >> grid[i];
        }
        auto first = [&](int r, int c, int t, auto &&first) -> void {
            if(r < 0 || r >= n || c < 0 || c >= m || (grid[r][c] != 'F' && grid[r][c] != '.')) return;
            grid[r][c] = 'F';
            first(r + dr[t], c + dc[t], t, first);
        };
        auto second = [&](int r, int c, int t1, int t2, auto &&second) -> void {
            if(r < 0 || r >= n || c < 0 || c >= m || (grid[r][c] != 'F' && grid[r][c] != '.')) return;
            grid[r][c] = 'F';
            first(r + dr[t2], c + dc[t2], t2, first);
            second(r + dr[t1], c + dc[t1], t1, t2, second);
        };
        rep(i, 0, n){
            rep(j, 0, m){
                int dir = -1;
                if(grid[i][j] == 'V'){
                    dir = 1;
                } else if(grid[i][j] == '>') dir = 7;
                else if(grid[i][j] == '<') dir = 3;
                else if(grid[i][j] == '^') dir = 5;
                if(dir != -1){
                    second(i + dr[(dir-1+8)%8], j + dc[(dir-1+8)%8], (dir-1+8)%8, dir, second);
                    second(i + dr[(dir+1)%8], j + dc[(dir+1)%8], (dir+1)%8, dir, second);
                    first(i + dr[dir], j + dc[dir], dir, first);
                }
            }
        }
        cout << "Map #" << (cn+1) << ":\n";
        rep(i, 0, n){
            cout << grid[i] << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}
