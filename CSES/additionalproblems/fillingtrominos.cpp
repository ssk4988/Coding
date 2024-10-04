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

vvi grid;
int t = 0;

void solve23(int i, int j)
{
    grid[i][j] = grid[i + 1][j] = grid[i + 1][j + 1] = t++;
    grid[i][j + 1] = grid[i][j + 2] = grid[i + 1][j + 2] = t++;
}

void solve32(int i, int j)
{
    grid[i][j] = grid[i + 1][j] = grid[i][j + 1] = t++;
    grid[i + 2][j] = grid[i + 1][j + 1] = grid[i + 2][j + 1] = t++;
}

void solve23k(int r1, int r2, int c1, int c2)
{
    for (int i = r1; i < r2; i += 2)
    {
        for (int j = c1; j < c2; j += 3)
        {
            solve23(i, j);
        }
    }
}

void solve56(int r1, int r2, int c1, int c2)
{
    solve23k(r1 + 3, r2, c1, c2);
    int i = r1;
    for (int j = c1; j < c2; j += 2)
    {
        solve32(i, j);
    }
}

void solve59(int r1, int r2, int c1, int c2) {
    solve32(r1, c1);
    solve32(r1, c1+2);
    solve23(r1+3, c1);
    solve23(r1, c1+4);
    solve32(r1, c1+7);
    grid[r1+3][c1+3] = grid[r1+4][c1+3] = grid[r1+4][c1+4] = t++;
    grid[r1+3][c1+3+2] = grid[r1+4][c1+3+2] = grid[r1+4][c1+4+2] = t++;
    grid[r1-1+3][c1+3+3] = grid[r1-1+4][c1+3+3] = grid[r1-1+4][c1+3+4] = t++;
    grid[r1+2][c1+4] = grid[r1+3][c1+4] = grid[r1+2][c1+5] = t++;
    grid[r1+4][c1+7] = grid[r1+4][c1+8] = grid[r1+3][c1+8] = t++;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    if ((n * m) % 3 != 0 || min(n, m) <= 1)
    {
        cout << "NO\n";
        return;
    }
    bool sw = false;
    if (m % 2 == 0 && n % 3 == 0)
    {
        sw = !sw;
        swap(n, m);
    }
    if (n % 2 == 0 && m % 3 == 0)
    {
        grid = vvi(n, vi(m, -1));
        solve23k(0, n, 0, m);
        goto end;
    }
    if (m % 3 != 0)
    {
        swap(n, m);
        sw = !sw;
    }
    // odd num, 3k
    if (m == 3 || n == 3)
    {
        cout << "NO\n";
        return;
    }
    grid = vvi(n, vi(m, -1));
    for (int r = n; r > 5; r -= 2)
    {
        solve23k(r - 2, r, 0, m);
    }
    // r = 5
    int c;
    for (c = m; c > 9; c -= 6)
    {
        solve56(0, 5, c-6, c);
    }
    if(c == 6) {
        solve56(0, 5, 0, 6);
    } else solve59(0, 5, 0, 9);

end:
    cout << "YES\n";
    if(sw) {
        vvi cp(m, vi(n));
        rep(i, 0, n){
            rep(j, 0, m){
                cp[j][i] = grid[i][j];
            }
        }
        swap(n, m);
        swap(cp, grid);
    }

    vvi adj(t);
    vpi dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    rep(i, 0,n)
        rep(j, 0, m)
            assert(grid[i][j] != -1);
    rep(i, 0,n){
        rep(j, 0, m){
            assert(grid[i][j] != -1);
            for(auto [dr, dc] : dirs){
                int i1 = i + dr, j1 = j + dc;
                if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
                if(grid[i1][j1] != grid[i][j]) {
                    adj[grid[i][j]].pb(grid[i1][j1]);
                }
            }
        }
    }
    vi col(t, -1);
    rep(i, 0, t){
        sort(all(adj[i]));
        adj[i].erase(unique(all(adj[i])), adj[i].end());
        int unused = 0;
        set<int> seen;
        for(int j : adj[i]){
            if(col[j] != -1) {
                seen.insert(col[j]);
            }
        }
        for(int j : seen) if(unused == j) unused++;
        col[i] = unused;
    }
    rep(i, 0, n){
        rep(j, 0, m){
            grid[i][j] = col[grid[i][j]];
            cout << char('A' + grid[i][j]);
        }
        cout << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc) solve();

    return 0;
}
