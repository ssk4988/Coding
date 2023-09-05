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
    // int n = 10;
    // vvi grid(n, vi(n));
    // vvi sus;
    // rep(i, 0, n){
    //     rep(j, 0, n){
    //         set<int> stuff;
    //         rep(k, 0, i) stuff.insert(grid[k][j]);
    //         rep(k, 0, j) stuff.insert(grid[i][k]);
    //         int mex = 0;
    //         for(int i : stuff){
    //             if(mex == i) mex++;
    //             else break;
    //         }
    //         grid[i][j] = mex;
    //         string res = to_string(grid[i][j]);
    //         while(sz(res) < 2) res = ' ' + res;
    //         cout << res << " ";
    //         if(grid[i][j] != (i ^ j)){
    //             sus.pb({i, j, grid[i][j], i ^ j});
    //         }
    //     }
    //     cout << nL;
    // }
    // rep(i, 0, sz(sus)){
    //     cout << sus[i][0] << " " << sus[i][1] << " " << sus[i][2] << " " << sus[i][3] << nL;
    // }
    int x, y; cin >> x >> y; x--; y--;
    cout << (x ^ y) << nL;

    return 0;
}
