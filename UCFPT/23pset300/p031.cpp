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

int n;
vvi grid, ns;
int wkings = 0;
vvi ds = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
vvi ds2 = {{2, 2}, {2, -2}, {-2, -2}, {-2, 2}}; 
vvi ds3 = {{2, 2}, {2, -2}, {-2, -2}, {-2, 2}, {0, 2}, {2, 0}, {-2, 0}, {0, -2}}; 
bool inbound(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}
int dist(int x1, int y1, int x2, int y2){
    return abs(x2 -x1) + abs(y1 - y2);
}

bool bt(int x, int y, int d){
    if(d == wkings){
        return true;
    }
    rep(i, 0, 4){
        int x1 = x + ds[i][0], y1 = y + ds[i][1];
        int x2 = x + ds2[i][0], y2 = y + ds2[i][1];
        if(inbound(x1, y1) && grid[x1][y1] == 1 && inbound(x2, y2) && grid[x2][y2] == 0){
            grid[x][y] = 0;
            grid[x1][y1] = 0;
            bool impossible = false, cond = false;
            rep(i1, 0, 8){
                int x22 = x1 + ds3[i1][0], y22 = y1 + ds3[i1][1];
                if(!inbound(x22, y22) || dist(x22, y22, x2, y2) == 1) continue; 
                ns[x22][y22]--;
                if(ns[x22][y22] == 0 && grid[x22][y22] == 1){
                    // impossible = true;
                }
            }
            grid[x2][y2] = 2;
            if(!impossible) cond = bt(x2, y2, d + 1);
            grid[x][y] = 2;
            grid[x1][y1] = 1;
            rep(i1, 0, 8){
                int x22 = x1 + ds3[i1][0], y22 = y1 + ds3[i1][1];
                if(!inbound(x22, y22) || dist(x22, y22, x2, y2) == 1) continue; 
                ns[x22][y22]++;
            }
            grid[x2][y2] = 0;
            if(cond) return true;
        }
    }
    return false;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    grid = vvi(n, vi(n));
    ns = vvi(n, vi(n));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n){
            if(str[j] == 'W'){
                grid[i][j] = 1;
                wkings++;
            }
            if(str[j] == 'B') grid[i][j] = 2;
        }
    }
    
    rep(i, 0, n){
        rep(j, 0, n){
            // if(grid[i][j] != 1) continue;
            rep(k, 0, 8){
                int x2 = i + ds3[k][0], y2 = j + ds3[k][1];
                if(inbound(x2, y2) && grid[x2][y2] == 1){
                    ns[i][j]++;
                }
            }
        }
    }
    int ans= 0;
    rep(i, 0, n){
        rep(j, 0, n){
            if(grid[i][j] == 2 && bt(i, j, 0)){
                ans++;
            }
        }
    }
    cout << ans << "\n";

    
    return 0;
}