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
    int n; cin >> n;
    vvi grid(n, vi(n));
    grid[0][0] = 1;
    int qs = 0;
    auto oddquery = [&](int r1, int c1, int r2, int c2) -> int {
        cout << "? " << r1+1 << " " << c1+1 << " " << r2+1 << " " << c2+1 << endl;
        qs++;
        assert(qs <= n * n);
        int res; cin >> res;
        return res;
    };
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == 0 && j == 0 || i == n - 1 && j == n - 1) continue;
            if((i + j) % 2 == 1) continue;
            if(i % 2 == 0){
                if(i){
                    grid[i][j] = oddquery(i-2, j, i, j) ^ grid[i-2][j] ^ 1;
                } else{
                    grid[i][j] = oddquery(i, j-2, i, j) ^ grid[i][j-2] ^ 1;
                }
            } else{
                grid[i][j] = oddquery(i-1, j-1, i, j) ^ grid[i-1][j-1] ^ 1;
            }
        }
    }
    vvi isp(n, vi(n));
    isp[0][1] = 1;
    // p == grid[0][1]
    rep(i, 0, n){
        if(i % 2 == 0){
            for(int j = 1; j < n; j += 2){
                if(i == 0 && j == 1) continue; // p
                else if(i == 0) isp[i][j] = oddquery(i, j-2, i, j) ^ isp[i][j-2] ^ 1;
                else isp[i][j] = oddquery(i-1, j-1, i, j) ^ isp[i-1][j-1] ^ 1;
            }
        } else {
            for(int j = n-1; j >= 0; j -= 2){
                if(j == 0){
                    isp[i][j] = oddquery(i, j, i, j+2) ^ isp[i][j+2] ^ 1;
                } else {
                    isp[i][j] = oddquery(i-1, j-1, i, j) ^ isp[i-1][j-1] ^ 1;
                }
            }
        }
    }
    auto findpal = [&](vvi &g, int startr, int startc, int targetr, int targetc, int curr, int curc, vi &path, auto&& findpal) -> bool {
        if(curr > targetr || curc > targetc) return false;
        path.pb(g[curr][curc]);
        if(sz(path) == 4){
            vi path1(path);
            reverse(all(path1));
            if(path == path1) return true;
            path.pop_back();
            return false;
        }
        if(findpal(g, startr, startc, targetr, targetc, curr+1, curc, path, findpal)) return true;
        if(findpal(g, startr, startc, targetr, targetc, curr, curc+1, path, findpal)) return true;
        path.pop_back();
        return false;
    };
    vector<vvi> gpos(2, vvi(n, vi(n))); // 0 is p=0, 1 is p=1
    rep(t, 0, 2){
        rep(i, 0, n){
            rep(j, 0, n){
                if((i + j) % 2 == 0) gpos[t][i][j] = grid[i][j];
                else gpos[t][i][j] = isp[i][j] ^ 1 ^ t;
            }
        }
    }
    int p = -1;
    rep(i, 0, n){
        rep(j, 0, n){
            rep(inc, 0, 4){
                int i1 = i + inc, j1 = j + 3 - inc;
                if(i1 >= n || j1 >= n) continue;
                vi path;
                bool res0 = findpal(gpos[0], i, j, i1, j1, i, j, path, findpal);
                path.clear();
                bool res1 = findpal(gpos[1], i, j, i1, j1, i, j, path, findpal);
                if(res0 != res1){
                    int res = oddquery(i, j, i1, j1);
                    if(res == int(res0)) p = 0;
                    else p = 1;
                    goto fnd;
                }
            }
        }
    }
    fnd:
    assert(p != -1);
    vvi& ans = gpos[p];
    cout << "! " << endl;
    rep(i, 0, n){
        rep(j, 0, n){
            cout << ans[i][j];
        }
        cout << endl;
    }
    
    return 0;
}
