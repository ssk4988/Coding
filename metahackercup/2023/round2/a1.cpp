#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

vi dr{1, 0, -1, 0};
vi dc{0, 1, 0, -1};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int r, c; cin >> r >> c;
        vvi grid(r, vi(c));
        rep(i, 0, r){
            string str; cin >> str;
            rep(j, 0, c){
                if(str[j] == 'B') grid[i][j] = 1;
                if(str[j] == 'W') grid[i][j] = 2;
            }
        }
        bool canrem = false;
        rep(i, 0, r){
            rep(j, 0, c){
                if(grid[i][j] != 0) continue;
                grid[i][j] = 1;
                vvi comp(r, vi(c, -1));
                int numcomps = 0;
                vi compcnt;
                auto dfs = [&](int row, int col, auto &&dfs)-> void {
                    comp[row][col] = numcomps;
                    rep(k, 0, 4){
                        if(row + dr[k] < 0 || row + dr[k] >= r || col + dc[k] < 0 || col + dc[k] >= c) continue;
                        if(grid[row + dr[k]][col + dc[k]] == 0) compcnt.back()++;
                        if(grid[row + dr[k]][col + dc[k]] == 2 && comp[row + dr[k]][col + dc[k]] == -1) dfs(row + dr[k], col + dc[k], dfs);
                    }
                };
                // cout << "now testing " << i << " " << j << endl;
                rep(i1, 0, r){
                    rep(j1, 0, c){
                        if(grid[i1][j1] == 2 && comp[i1][j1] == -1){
                            compcnt.pb(0);
                            dfs(i1, j1, dfs);
                            numcomps++;
                        }
                    }
                }
                grid[i][j] = 0;
                for(int v : compcnt) if(v == 0) canrem = true;
            }
        }
        cout << "Case #" << (cn + 1) << ": " << (canrem ? "YES" : "NO") << endl;
    }
    
    return 0;
}
