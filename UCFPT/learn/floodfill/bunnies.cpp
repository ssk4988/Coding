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
    rep(cn,0,nc){
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        rep(i, 0, n){
            cin >> grid[i];
        }
        vvi comp(n, vi(m, -1));
        auto dfs = [&](int r, int c, auto &&dfs)->void {
            rep(t, 0, 4){
                int r1 = r + dr[t], c1 = c + dc[t];
                if(r1 < 0 || r1 >= n || c1 < 0 || c1 >= m) continue;
                if(comp[r1][c1] != -1 || grid[r1][c1] == '#') continue;
                comp[r1][c1] = comp[r][c];
                dfs(r1, c1, dfs);
            }
        };
        int cs = 0;
        pii pet, cot;
        rep(i, 0, n){
            rep(j, 0, m){
                if(grid[i][j] != '#' && comp[i][j] == -1){
                    comp[i][j] = cs++;
                    dfs(i, j, dfs);
                }
                if(grid[i][j] == 'P') pet = {i, j};
                if(grid[i][j] == 'C') cot = {i, j};
            }
        }
        cout << (comp[pet.f][pet.s] == comp[cot.f][cot.s] ? "yes" : "no") << "\n";

    }
    
    return 0;
}
