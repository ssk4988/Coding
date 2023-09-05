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
        vector<pair<pi, pi>> coords;
        vvi vert(n - 1);
        vvi horiz(m - 1);
        rep(i, 0, n){
            rep(j, 0, m){
                if(i + 1 < n && grid[i][j] == 'U' && grid[i + 1][j] == 'D'){
                    vert[i].pb(sz(coords));
                    coords.pb({{i, j}, {i + 1, j}});
                }
                if(j + 1 < m && grid[i][j] == 'L' && grid[i][j +1] == 'R'){
                    horiz[j].pb(sz(coords));
                    coords.pb({{i,j}, {i,j+1}});
                }
            }
        }
        bool works = true;
        rep(i, 0, sz(vert)){
            if(sz(vert[i]) % 2 != 0) works = false;
        }
        rep(i, 0, sz(horiz)){
            if(sz(horiz[i]) % 2 != 0) works = false;
        }
        if(!works){
            cout << "-1\n";
            continue;
        }
        rep(i, 0, sz(vert)){
            rep(j, 0, sz(vert[i])){
                int u = vert[i][j];
                auto [p1, p2] = coords[u];
                auto [r1, c1] = p1;
                auto [r2, c2] = p2;
                grid[r1][c1] = j % 2 == 0 ? 'W' : 'B';
                grid[r2][c2] = j % 2 == 0 ? 'B' : 'W';
            }
        }
        rep(i, 0, sz(horiz)){
            rep(j, 0, sz(horiz[i])){
                int u = horiz[i][j];
                auto [p1, p2] = coords[u];
                auto [r1, c1] = p1;
                auto [r2, c2] = p2;
                grid[r1][c1] = j % 2 == 0 ? 'W' : 'B';
                grid[r2][c2] = j % 2 == 0 ? 'B' : 'W';
            }
        }
        rep(i, 0, n){
            cout << grid[i] << nL;
        }
    }
    
    return 0;
}
