#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define pb push_back

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m, n; cin >> m >> n;
    vvi grid(n, vi(m));
    vvi suff(n + 1, vi(m + 1));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            grid[i][j] = str[j] == '#';
        }
    }
    for(int i = n - 1; i >= 0; i--){
        for(int j = m - 1; j >= 0; j--){
            suff[i][j] = grid[i][j] + suff[i + 1][j] + suff[i][j + 1] - suff[i + 1][j + 1];
        }
    }
    auto calc = [&](int i, int j, int di, int dj) -> int {
        return suff[i][j] - suff[i + di][j] - suff[i][j + dj] + suff[i + di][j + dj];
    };
    auto allblack = [&](int i, int j, int di, int dj) -> bool {
        return calc(i, j, di, dj) == di * dj;
    };
    auto allwhite = [&](int i, int j, int di, int dj) -> bool {
        return calc(i, j, di, dj) == 0;
    };
    vvi a = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };
    vvi b = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    vvi c = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    int acnt = 0, bcnt = 0, ccnt = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] != 0) continue;
            if(i + 1 >= n || j + 1 >= m || grid[i + 1][j + 1] != 1) continue;
            int lo = 1, hi = (m - 1) - (j + 1);
            while(lo < hi){
                int mid = lo + (hi - lo + 1) / 2;
                if(allblack(i + 1, j + 1, 1, mid)){
                    lo = mid;
                }
                else hi = mid - 1;
            }
            if(lo > hi) continue;
            int w = lo + 2;
            lo = 1, hi = (n - 1) - (i + 1);
            while(lo < hi){
                int mid = lo + (hi - lo + 1) / 2;
                if(allblack(i + 1, j + 1, mid, 1)){
                    lo = mid;
                }
                else hi = mid - 1;
            }
            if(lo > hi) continue;
            int h = lo + 2;
            // cout << i << " " << j << " " << w << " " << h << "\n";
            int y = 2 * h - 3 * w + 2;
            // cout << y << "\n";
            if(i + h - 1 >= n || j + w - 1 >= m) continue;
            if(y <= 0 || (w - 2 - y) % 2 != 0) continue;
            int x = (w - 2 - y) / 2;
            if(x <= 0) continue;
            // cout << i << " " << j << " " << w << " " << h << " " << x << " " << y << "\n";
            vi cdims = {1, x, y, x, 1}, rdims = {1, x, y, x, y, x, 1};
            vi cstart, rstart;
            cstart.pb(j);
            rstart.pb(i);
            for(int rd : rdims) rstart.pb(rstart.back() + rd);
            for(int cd : cdims) cstart.pb(cstart.back() + cd);
            vvi bd(sz(rdims), vi(sz(cdims)));
            bool valid = true;
            rep(ri, 0, sz(rdims)){
                if(!valid) break;
                rep(ci, 0, sz(cdims)){
                    if(!valid) break;
                    if(!(allblack(rstart[ri], cstart[ci], rdims[ri], cdims[ci]) || allwhite(rstart[ri], cstart[ci], rdims[ri], cdims[ci]))){
                        valid = false;
                        break;
                    }
                    bd[ri][ci] = allblack(rstart[ri], cstart[ci], rdims[ri], cdims[ci]);
                }
            }
            if(valid){
                if(bd == a) acnt++;
                if(bd == b) bcnt++;
                if(bd == c) ccnt++;
            }
        }
    }
    cout << acnt << " " << bcnt << " " << ccnt << "\n";

    return 0;
}
